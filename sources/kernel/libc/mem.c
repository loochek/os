#include "mem.h"

void memcpy(char *source, char *dest, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
	{
        *(dest + i) = *(source + i);
    }
}

void memset(unsigned char *dest, unsigned char val, unsigned int len)
{
    unsigned char *temp = (unsigned char *)dest;
    for ( ; len != 0; len--)
		*temp++ = val;
}
