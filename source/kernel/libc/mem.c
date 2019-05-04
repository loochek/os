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

void itoa(int n, char str[])
{
	int neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	int i = 0;
	while (n > 0)
	{
		str[i++] = '0' + n % 10;
		n = n / 10;
	}
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str);
}
