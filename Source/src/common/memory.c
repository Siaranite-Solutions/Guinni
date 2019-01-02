/*
 * memory.c
 * Provides a simple implemenation of common C
 * memory functions
 */

#include <stddef.h>
#include <stdint.h>
#include <kernel/common.h>


void *memcpy(void *dest, void *src, size_t size)
{
	for (int i = 0; i < size; i++)
		((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
}

void *memset(void *source, uint8_t b, size_t size)
{
	for (int i = 0; i < size; i++)
		((uint8_t *)source)[i] = b;
}
