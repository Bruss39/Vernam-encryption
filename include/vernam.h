#ifndef VERNAM_H
#define VERNAM_H

/*
Create a new key and save it to *outPath.
Return true on success, false on error.
*/
void generate_key(char *outPath, int size_in_bit);

#endif
