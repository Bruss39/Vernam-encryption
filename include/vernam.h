#ifndef VERNAM_H
#define VERNAM_H

#include <stdio.h>
#include <stdbool.h>

/*
Create a new key in the folder at *outPath, without overwriting files.
Save the resulting path in outPath (256 bytes).
Return true on success, false on error.
*/
bool generate_key(char *outPath, long long size, const char *key_name);

/*
Apply XOR for symmetric file encryption/decryption.
Create a new output file in the folder at out_path.
Save the resulting path in out_path (256 bytes). Keep the original files.
Return true on success, false otherwise.
*/
bool xor_cipher(FILE *data, FILE *key, char *out_path);

#endif
