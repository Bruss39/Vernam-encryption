#ifndef VERNAM_H
#define VERNAM_H

#include <stdio.h>
#include <stdbool.h>

/*
Create a new key and save it to *outPath.
Return true on success, false on error.
*/
bool generate_key(char *outPath, long long size, char *key_name);

/*
Apply XOR for symmetric file encryption/decryption.
WARNING: data file will be overwritten by its decrypted/encrypted version!
Return true on success, false otherwise.
*/
bool xor_cipher(FILE *data, FILE *key);

#endif
