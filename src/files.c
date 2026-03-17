#define _FILE_OFFSET_BITS 64

#include "files.h"
#include <stdio.h>
#include <sys/types.h>

#ifdef _WIN32
    #define file_seek  _fseeki64
    #define file_tell  _ftelli64
    typedef long long file_offset_t;
#else
    #define file_seek  fseeko
    #define file_tell  ftello
    typedef off_t file_offset_t;
#endif

long long get_size_file(FILE *file){
    long long size = 0;

    if (file_seek(file, 0, SEEK_END)){  // Move at the end of file
        return -1;  // Failed 
    }

    size = file_tell(file);  // Get the distance form the start in byte
    if (size < 0){
        return -1;  // Failed 
    }

    rewind(file);  // Move file pointer to the beginning
    return size;
}


bool file_exist(const char *path){
    FILE *file = fopen(path, "rb");  // Try open file

    if (file == NULL){  // Exit if fopen() fails
        return false;
    }
    
    fclose(file);
    return true;
}
