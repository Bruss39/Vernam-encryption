#include <stdio.h>
#include <stdbool.h>
#include "input.h"
#include "files.h"


int main() {
    FILE *file;
    FILE *key;

    char file_path[256];
    char key_path[256];

    printf ("=====  VERNAM CIPHER  =====");

    // GET INPUT
    printf ("\n\nEnter file path: ");  // Ask for the file path to encrypt
    get_path(file_path);
    
    char answer[8];
    printf ("\nHave you a key file? (Y/n) ");  // Ask for the key path (default = Y)
    fgets(answer, sizeof(answer), stdin);

    if (answer[0] == '\n' || answer[0] == 'y' || answer[0] == 'Y'){  // Get the key if the users has one
        printf ("Enter key file path: ");
        get_path(key_path);
    }
    else {
        printf ("Enter path to save the new key: ");
        // generate_key();  // Generate one
    }

    // open file
    // open key

    // XOR

    return 0;
}
