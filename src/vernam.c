#include "vernam.h"
#include "files.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <bcrypt.h>
    #include <ntstatus.h>
#endif


enum {
    BUFFER_SIZE = 65536  // 64 * 1024
};


#ifndef _WIN32
static bool linux_fill_random(unsigned char *buffer, size_t size)
{
    /*
    Linux version
    Fill buffer with random bytes.
    Return true on success.
    */
    FILE *random = fopen("/dev/urandom", "rb");
    if (random == NULL) return false;

    bool success = fread(buffer, 1, size, random) == size;
    if (fclose(random) != 0) success = false;
    return success;
}

#else
static bool win_fill_random(unsigned char *buffer, size_t size)
{
    /*
    Windows version
    Fill buffer with random bytes.
    Return true on success.
    */
    if (BCryptGenRandom(NULL, buffer, (ULONG)size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) == STATUS_SUCCESS)
        return true;
    
    return false;
}
#endif


bool generate_key(char *outPath, long long size, const char *key_name)
{
    if (size < 0){
        printf("ERROR: invalid file size");
        return false;
    }

    if (key_name[0] == '\0' || strchr(key_name, '/') || strchr(key_name, '\\')) {
        printf("ERROR: key name must not contain a path");
        return false;
    }

    char new_path[256];
    int length = snprintf(new_path, sizeof(new_path), "%s/%s.key", outPath, key_name);
    if (length < 0 || length >= (int)sizeof(new_path)) {
        printf("ERROR: key path is too long");
        return false;
    }

    FILE *file = fopen(new_path, "wbx");  // Create key file without overwriting
    if (file == NULL){
        printf("ERROR: cannot create key file (check folder and existing files)");
        return false;
    }
    strcpy(outPath, new_path);

    unsigned char buffer[BUFFER_SIZE];
    unsigned long long remaining = size;
    size_t chunk = 0;

    while(remaining > 0){
        if (remaining > BUFFER_SIZE) chunk = BUFFER_SIZE;
        else chunk = (size_t)remaining;

        // Fill buffer
#ifdef _WIN32
        if (!win_fill_random(buffer, chunk))
        {
            fclose(file);
            remove(outPath);
            printf("ERROR: failed in 'win_fill_random'");
            return false;
        }
#else
        if (!linux_fill_random(buffer, chunk))
        {
            fclose(file);
            remove(outPath);
            printf("ERROR: failed in 'linux_fill_random'");
            return false;
        }
#endif

        if (fwrite(buffer, 1, chunk, file) != chunk)
        {
            fclose(file);
            remove(outPath);
            printf("ERROR: failed to write file");
            return false;
        }
        remaining -= chunk;
    }

    if (fclose(file) != 0) {
        remove(outPath);
        printf("ERROR: failed to close key file");
        return false;
    }
    return true;
}


bool xor_cipher(FILE *data, FILE *key, char *out_path)
{
    unsigned char buffer_data[BUFFER_SIZE];
    unsigned char buffer_key[BUFFER_SIZE];

    srand(time(NULL));

    int random = rand() % 1000;  // for file extension
    
    long long data_size = get_size_file(data);
    long long key_size = get_size_file(key);
    if (data_size < 0 || key_size < 0 || data_size != key_size) {
        fprintf(stderr, "\nERROR: invalid data or key size");
        return false;
    }

    unsigned long long remaining = data_size;
    size_t chunk = 0;
    size_t n_data = 0;
    size_t n_key = 0;

    // Create a new output file, trying another number if it already exists
    char new_path[256];
    FILE *out = NULL;
    for (int attempt = 0; attempt < 1000; attempt++) {
        int length = snprintf(new_path, sizeof(new_path), "%s/output.%d", out_path, (random + attempt) % 1000);
        if (length < 0 || length >= (int)sizeof(new_path)) {
            fprintf(stderr, "\nERROR: output path is too long");
            return false;
        }

        out = fopen(new_path, "wbx");
        if (out != NULL || errno != EEXIST) break;
    }

    if (out == NULL)
    {
        fprintf (stderr, "\n\nERROR: cannot create an output file in '%s' folder", out_path);
        return false;
    }
    strcpy(out_path, new_path);

    while (remaining > 0)
    {
        // check buffer size
        if (remaining > BUFFER_SIZE) chunk = BUFFER_SIZE;
        else chunk = (size_t)remaining;

        // read files
        n_data = fread(buffer_data, 1, chunk, data);
        n_key = fread(buffer_key, 1, chunk, key);

        if (n_data != chunk || n_key != chunk)
        {
            fprintf (stderr, "\n\nERROR: failed to read files");
            fclose(out);
            remove(out_path);
            return false;
        }

        // apply xor and save output
        for (size_t i=0; i<chunk; i++) buffer_data[i] ^= buffer_key[i];  // xor

        if(fwrite(buffer_data, 1, chunk, out) != chunk)
        {
            fprintf (stderr, "\n\nERROR: failed to write to '%s'", out_path);
            fclose(out);
            remove(out_path);
            return false;
        }

        remaining -= chunk;
    }

    rewind(data);
    rewind(key);
    if (fclose(out) != 0) {
        remove(out_path);
        fprintf(stderr, "\nERROR: failed to close output file");
        return false;
    }
    return true;
}
