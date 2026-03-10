#include "input.h"
#include <stdio.h>
#include <string.h>


bool get_input(char path[]) {
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
