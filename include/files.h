#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdbool.h>

long get_size_file(FILE *file);
bool file_exist(const char *path);

#endif
