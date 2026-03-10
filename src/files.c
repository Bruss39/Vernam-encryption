#include "files.h"
#include <stdio.h>
#include <stdbool.h>

long get_size_file(FILE *file){
    /*
    Return size of the file [byte]
    else return -1 if an error occurred
    */

    long size = 0;

    if (fseek(file, 0, SEEK_END)){  // Move at the end of file
        return -1;  // Failed 
    }

    size = ftell(file);  // Get the distance form start in byte
    if (size < 0){
        return -1;  // Failed 
    }

    rewind(file);  // Move file pointer to the beginning
    return size;
}


bool file_exist(const char *path){
    /*
    Try to open the file at the given path.
    Return true if successful.
    */

    FILE *file = fopen(path, "rb");  // Try open file

    if (file == NULL){  // Exit if fopen() fails
        return false;
    }
    
    fclose(file);
    return true;
}
