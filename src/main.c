#include <stdio.h>
#include <stdbool.h>
#include "input.h"


int main() {
    printf ("=====  VERNAM CIPHER  =====");

    char file_path[256];
    char key_path[256];
    bool need_key;  // True if user hasn't key file

    do {
        printf ("\n\nEnter file path: ");
    } while (get_input(file_path) == 0);

    printf ("\n\nEnter key file path (leave empty to generate one): ");
    need_key = get_input(key_path);

    return 0;
}
