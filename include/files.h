#ifndef FILES_H
#define FILES_H

#include <stdbool.h>
#include <stdio.h>

/*
Return size of the file [byte].
If an error occurred, return -1.
*/
long long get_size_file(FILE *file);

/*
Try to open the file at the given path.
Return true if path exist.
*/
bool file_exist(const char *path);

#endif
