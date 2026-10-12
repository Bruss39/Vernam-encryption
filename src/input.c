#include "input.h"
#include "files.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool read_input(char *input, size_t size) {
    /*
    Read input into the buffer.
    Return false on input error, true otherwise.
    Remove trailing '\n' if present.
    */

    if (fgets(input, size, stdin) == NULL)
        return false;

    if (strchr(input, '\n') == NULL) {
        int next = getchar();
        if (next != '\n' && next != EOF) {
            while (next != '\n' && next != EOF) next = getchar();
            printf("Input too long, retry.\n");
            input[0] = '\0';
            return true;
        }
    }

    input[strcspn(input, "\r\n")] = '\0';
    return true;
}


static bool is_empty_path(const char *path) {
    return (path == NULL || path[0] == '\0');
}


bool get_existing_file_path(char *path) {
    while (true) {
        if (!read_input(path, 256)) return false;

        if (is_empty_path(path)) {
            printf("Retry: ");
            continue;
        }

        if (!file_exist(path)) {
            printf("Cannot open the file, retry: ");
            continue;
        }

        return true;
    }
}


bool get_new_file_path(char *path) {
    while (true) {
        if (!read_input(path, 256)) return false;

        if (is_empty_path(path)) {
            printf("Retry: ");
            continue;
        }

        return true;
    }
}
