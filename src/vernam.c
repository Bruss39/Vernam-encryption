#include "vernam.h"
#include "files.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #include <bcrypt.h>
    #include <ntstatus.h>
#endif


enum {
    BUFFER_SIZE = 65536  // 64 * 1024
};


static bool linux_fill_random(unsigned char *buffer, size_t size)
{
    /*
    Linux version
    Fill buffer with random bytes.
    Return true on success.
    */
    return 0;
}


static bool win_fill_random(unsigned char *buffer, size_t size)
{
    /*
    Windows version
    Fill buffer with random bytes.
    Return true on success.
    */
    if (BCryptGenRandom(NULL, buffer, size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) == STATUS_SUCCESS)
        return true;
    
     return false;
}


bool generate_key(char *outPath, long long size, char *key_name)
{
    if (size <= 0){
        printf("ERROR: size <= 0");
        return false;
    }

    strcat(key_name, ".key");  // Append key name to path
    strcat(outPath, "/");
    strcat(outPath, key_name);

    FILE *file = fopen(outPath, "wb");  // Create key file
    if (file == NULL){
        printf("ERROR: file == NULL");
        return false;
    }

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
            printf("ERROR: failled in 'win_fill_random'");
            return false;
        }
#else
        if (!linux_fill_random(buffer, chunk))
        {
            fclose(file);
            printf("ERROR: failled in 'linux_fill_random'");
            return false;
        }
#endif

        if (fwrite(buffer, 1, chunk, file) != chunk)
        {
            fclose(file);
            printf("ERROR: failled to write file");
            return false;
        }
        remaining -= chunk;
    }

    fclose(file);
    return true;
}


bool xor_cipher(FILE *data, FILE *key, char *out_path)
{
    unsigned char buffer_data[BUFFER_SIZE];
    unsigned char buffer_key[BUFFER_SIZE];

    srand(time(NULL));

    char *out_name = "output";
    char file_extension[5];
    int random = rand() % 1000;  // for file extension
    
    unsigned long long remaining = get_size_file(data);;
    size_t chunk = 0;
    size_t n_data = 0;
    size_t n_key = 0;

    // create output file
    strcat(out_path, "/");
    strcat(out_path, out_name);
    sprintf(file_extension, "%d", random);
    strcat(out_path, ".");
    strcat(out_path, file_extension);
    FILE *out = fopen(out_path, "wb");

    if (out == NULL)
    {
        fprintf (stderr, "\n\nERROR: cannot create '%s' in '%s' folder", out_name, out_path);
        return false;
    }

    while (remaining > 0)
    {
        // check buffer size
        if (remaining > BUFFER_SIZE) chunk = BUFFER_SIZE;
        else chunk = remaining;

        // read files
        n_data = fread(buffer_data, 1, chunk, data);
        n_key = fread(buffer_key, 1, chunk, key);

        if (n_data != n_key)
        {
            fprintf (stderr, "\n\nERROR: failed to read files");
            return false;
        }

        // apply xor and save output
        for (size_t i=0; i<chunk; i++) buffer_data[i] ^= buffer_key[i];  // xor

        if(fwrite(buffer_data, 1, chunk, out) != chunk)
        {
            fprintf (stderr, "\n\nERROR: failed to write to '%s'", out_name);
            return false;
        }

        remaining -= chunk;
    }

    rewind(data);
    rewind(key);
    fclose(out);
    return true;
}
