#include "vernam.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096

#ifdef _WIN32
    #include <windows.h>
    #include <bcrypt.h>
    #include <ntstatus.h>
#endif


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


static bool read_bytes(unsigned char *buffer, size_t size)
{
    /*
    Read bytes from a file and store them in a buffer.
    Return true on success.
    */
    return 0;
}


bool generate_key(char *outPath, long long size, char *key_name)
{
    if (size <= 0){
        printf("ERROR: size <= 0");
        return false;
    }

    strcat(key_name, ".key");  // Append key name to path
    strcat(outPath, "\\");
    strcat(outPath, key_name);

    FILE *file = fopen(outPath, "wb");  // Create key file
    if (file == NULL){
        printf("ERROR: file == NULL");
        return false;
    }

    unsigned char buffer[BUFFER_SIZE];
    long long remaining = size;
    size_t chunk = 0;

    while(remaining > 0){
        if (remaining > BUFFER_SIZE)
            chunk = BUFFER_SIZE;
        else
            chunk = (size_t)remaining;

        // Fill buffer
#ifdef _WIN32
        if (!win_fill_random(buffer, chunk)){
            fclose(file);
            printf("ERROR: failled in 'win_fill_random'");
            return false;
        }
#else
        if (!linux_fill_random(buffer, chunk)){
            fclose(file);
            printf("ERROR: failled in 'linux_fill_random'");
            return false;
        }
#endif

        if (fwrite(buffer, 1, chunk, file) != chunk){
            fclose(file);
            printf("ERROR: failled to write file");
            return false;
        }
        remaining -= chunk;
    }

    fclose(file);
    return true;
}


bool xor_cipher(FILE *data, FILE *key)
{
    return 0;
}
