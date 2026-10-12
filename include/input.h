#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stddef.h>

/*
Read a line without overflowing the buffer.
Return false on end of input or input error.
*/
bool read_input(char *input, size_t size);

/*
Read a path from input.
Retry until path is not empty and file exists.
Save result in path (256 bytes). Return false on input error.
*/
bool get_existing_file_path(char *path);

/*
Read a path from input.
Retry until path is not empty.
Save result in path (256 bytes). Return false on input error.
*/
bool get_new_file_path(char *path);

#endif
