#include "input.h"
#include "files.h"
#include "vernam.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main() {
    FILE *file;
    FILE *key;

    char file_path[256];
    char key_path[256];
    char out_path[256];
    bool already_correct_out_path = false;

    long long key_size = 0;

    printf ("===============  VERNAM CIPHER  ===============");

    // === GET INPUT ===
    printf ("\n\nEnter file path: ");  // Ask for the file path to encrypt
    get_existing_file_path(file_path);
    printf ("file_path:   \"%s\"", file_path);
    file = fopen(file_path, "rb");  // Open data file
    
    char answer[8];
    printf ("\n\nHave you a key file? (Y/n) ");  // Ask for the key path (default = Y)
    fgets(answer, sizeof(answer), stdin);

    if (answer[0] == '\n' || answer[0] == 'y' || answer[0] == 'Y'){  // Get the key if the users has one
        printf ("Enter key file path: ");
        get_existing_file_path(key_path);
        printf ("key_path:   \"%s\"", key_path);
    }
    else {
        printf ("Enter folder where save the new key: ");
        get_new_file_path(key_path);
        
        strcpy(out_path, key_path);  // get out_path for xor_cipher() function
        already_correct_out_path = true;

        char key_name[20];
        printf ("Choose a name for your new key: ");
        scanf("%s", key_name);

        key_size = get_size_file(file);

        if (!generate_key(key_path, key_size, key_name)){  // Generate one
            printf("\nERROR: failed to generate the key in path: \"%s\".", key_path);
            return 1;
        } else {
            printf("\nCorrectly generation of key at path: \"%s\".", key_path);
        }
    }
    key = fopen(key_path, "rb");  // Open key file

    if (!already_correct_out_path)
    {
        // derive out_path from key_path
        strcpy(out_path, key_path);
        char *last1 = strrchr(out_path, '/');
        char *last2 = strrchr(out_path, '\\');
        char *last = last1 > last2 ? last1 : last2;
        if (last) *last = '\0';
    }

    // === XOR ===
    if (get_size_file(file) == get_size_file(key))
    {
        if (xor_cipher(file, key, out_path)) printf ("\n\nOutput saved in '%s'\nBye! (^._.^)", out_path);
        else printf ("\nError occurred in XOR function");
    } else {
        printf("\nWARNING: data and key files have different sizes!");
        return 1;
    }

    fclose(file);
    fclose(key);
    return 0;
}
