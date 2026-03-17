#include "input.h"
#include "files.h"
#include "vernam.h"

#include <stdio.h>
#include <stdbool.h>


int main() {
    FILE *file;
    FILE *key;

    char file_path[256];
    char key_path[256];
    long long key_size = 0;

    printf ("===============  VERNAM CIPHER  ===============");

    // GET INPUT
    printf ("\n\nEnter file path: ");  // Ask for the file path to encrypt
    get_existing_file_path(file_path);
    printf ("file_path:   \"%s\"", file_path);
    file = fopen(file_path, "rb");  // Open data file
    
    // Ask for the key path (default = Y)
    char answer[8];
    printf ("\n\nHave you a key file? (Y/n) ");
    fgets(answer, sizeof(answer), stdin);

    if (answer[0] == '\n' || answer[0] == 'y' || answer[0] == 'Y'){  // Get the key if the users has one
        printf ("Enter key file path: ");
        get_existing_file_path(key_path);
        printf ("\nkey_path:   \"%s\"", key_path);
    }
    else {
        printf ("Enter folder where save the new key: ");
        get_new_file_path(key_path);

        char key_name[20];
        printf ("Choose a name for your new key: ");
        scanf("%s", key_name);

        key_size = get_size_file(file);

        if (!generate_key(key_path, key_size, key_name)){  // Generate one
            printf("\nFailed to generate the key in path: \"%s\".", key_path);
            return 1;
        } else {
            printf("\nCorrectly generation of key at path: \"%s\".", key_path);
        }
    }
    key = fopen(key_path, "rb");  // Open key file

    // XOR

    return 0;
}
