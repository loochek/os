#include "string.h"

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
