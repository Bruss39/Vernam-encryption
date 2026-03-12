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

    printf ("===============  VERNAM CIPHER  ===============");

    // GET INPUT
    printf ("\n\nEnter file path: ");  // Ask for the file path to encrypt
    get_existing_file_path(file_path);
    
    // Ask for the key path (default = Y)
    char answer[8];
    printf ("\nHave you a key file? (Y/n) ");
    fgets(answer, sizeof(answer), stdin);

    if (answer[0] == '\n' || answer[0] == 'y' || answer[0] == 'Y'){  // Get the key if the users has one
        printf ("Enter key file path: ");
        get_existing_file_path(key_path);
    }
    else {
        printf ("Enter a path to save the new key: ");
        get_new_file_path(key_path);

        //generate_key()  // Generate one
    }
    printf ("\nfile_path:   %s", file_path);
    printf ("\nkey_path:   %s", key_path);

    // open file
    // open key

    // XOR

    return 0;
}
