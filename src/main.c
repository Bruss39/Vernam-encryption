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
    if (!get_existing_file_path(file_path)) return 1;
    printf ("file_path:   \"%s\"", file_path);
    file = fopen(file_path, "rb");  // Open data file
    if (file == NULL) {
        fprintf(stderr, "\nERROR: cannot open data file.");
        return 1;
    }
    
    char answer[8];
    printf ("\n\nHave you a key file? (Y/n) ");  // Ask for the key path (default = Y)
    if (!read_input(answer, sizeof(answer))) {
        fclose(file);
        return 1;
    }

    if (answer[0] == '\0' || answer[0] == 'y' || answer[0] == 'Y'){  // Get the key if the users has one
        printf ("Enter key file path: ");
        if (!get_existing_file_path(key_path)) {
            fclose(file);
            return 1;
        }
        printf ("key_path:   \"%s\"", key_path);
    }
    else {
        printf ("Enter folder where save the new key: ");
        if (!get_new_file_path(key_path)) {
            fclose(file);
            return 1;
        }
        
        strcpy(out_path, key_path);  // get out_path for xor_cipher() function
        already_correct_out_path = true;

        char key_name[256];
        printf ("Choose a name for your new key: ");
        if (!get_new_file_path(key_name)) {
            fclose(file);
            return 1;
        }

        key_size = get_size_file(file);

        if (!generate_key(key_path, key_size, key_name)){  // Generate one
            printf("\nERROR: failed to generate the key in path: \"%s\".", key_path);
            fclose(file);
            return 1;
        } else {
            printf("\nKey generated at path: \"%s\".", key_path);
        }
    }
    key = fopen(key_path, "rb");  // Open key file
    if (key == NULL) {
        fprintf(stderr, "\nERROR: cannot open key file.");
        fclose(file);
        return 1;
    }

    if (!already_correct_out_path)
    {
        // derive out_path from key_path
        strcpy(out_path, key_path);
        char *last1 = strrchr(out_path, '/');
        char *last2 = strrchr(out_path, '\\');
        char *last = last1;
        if (last2 != NULL && (last == NULL || last2 > last)) last = last2;
        if (last == NULL) strcpy(out_path, ".");
        else if (last == out_path || (last == out_path + 2 && out_path[1] == ':')) last[1] = '\0';
        else *last = '\0';
    }

    // === XOR ===
    long long file_size = get_size_file(file);
    key_size = get_size_file(key);
    int result = 1;

    if (file_size < 0 || key_size < 0) {
        fprintf(stderr, "\nERROR: cannot read file sizes.");
    }
    else if (file_size == key_size)
    {
        if (xor_cipher(file, key, out_path)) {
            printf ("\n\nOutput saved in '%s'\nBye! (^._.^)\n", out_path);
            result = 0;
        }
        else printf ("\nError occurred in XOR function");
    } else {
        printf("\nWARNING: data and key files have different sizes!");
    }

    fclose(file);
    fclose(key);
    return result;
}
