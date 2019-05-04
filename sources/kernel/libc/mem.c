#include "mem.h"

void memcpy(char *source, char *dest, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
	{
        *(dest + i) = *(source + i);
    }
}

void memset(u8 *dest, u8 val, u32 len)
{
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--)
		*temp++ = val;
}