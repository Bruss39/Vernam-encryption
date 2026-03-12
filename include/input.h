#ifndef INPUT_H
#define INPUT_H

/*
Read a path from input.
Retry until path is not empty and file exists.
Save result in path.
*/
void get_existing_file_path(char *path);

/*
Read a path from input.
Retry until path is not empty.
Save result in path.
*/
void get_new_file_path(char *path);

#endif
