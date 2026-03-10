#include "input.h"
#include "files.h"
#include <stdio.h>
#include <string.h>


bool read_input(char *path) {
    /*
    Get input and save it in passed pointer.
    Return true if input was read successfully.
    */

    if (fgets(path, 256, stdin) != NULL) {  // Get path
        path[strcspn(path, "\n")] = '\0';   // Remove '\n' from the end
        return 1;
    }
    
    return 0;
}


void get_path(char *path){
    /*
    Get input and check if it isn't void or invalid.
    */

    while (true){
        if (read_input(path) == 0  ||  path[0] == '\0'){  // Retry if the input is void
            printf("Retry: ");
            continue;
        } else if (!file_exist(path)){
            printf("Cannot open the file, retry: ");  // Retry if the path is invalid
            continue;
        } else {
            break;
        }
    }
}
