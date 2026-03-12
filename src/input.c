#include "input.h"
#include "files.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


static bool read_path(char *path) {
    /*
    Read input into path.
    Return false on input error, true otherwise.
    Remove trailing '\n' if present.
    */

    if (fgets(path, 256, stdin) == NULL)
        return false;

    path[strcspn(path, "\n")] = '\0';
    return true;
}


static bool is_empty_path(const char *path) {
    return (path == NULL || path[0] == '\0');
}


void get_existing_file_path(char *path) {
    while (true) {
        if (!read_path(path) || is_empty_path(path)) {
            printf("Retry: ");
            continue;
        }

        if (!file_exist(path)) {
            printf("Cannot open the file, retry: ");
            continue;
        }

        break;
    }
}


void get_new_file_path(char *path) {
    while (true) {
        if (!read_path(path) || is_empty_path(path)) {
            printf("Retry: ");
            continue;
        }

        break;
    }
}
