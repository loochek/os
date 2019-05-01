#ifndef UTIL_H
#define UTIL_H

#include "types.h"

void memcpy(char *source, char *dest, int nbytes);
void memset(u8 *dest, u8 val, u32 len);
void itoa(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);

#endif