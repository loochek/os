#include "mem.h"

void memcpy(char *source, char *dest, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
	{
        *(dest + i) = *(source + i);
    }
}

void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--)
		*temp++ = val;
}

uint32_t free_mem_addr = 0x100000;

void* malloc(uint32_t size)
{
	uint32_t ret = free_mem_addr;
	free_mem_addr += size;
	return (void*)ret;
}
