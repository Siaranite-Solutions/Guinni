/*
 * portio.c
 * Provides several routines for dealing with low
 * level port IO
 */

#include <stdint.h>
#include <kernel/portio.h>


uint8_t inb(uint16_t port)
{
	uint8_t ret;

	asm volatile ("inb %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}

uint16_t inw(uint16_t port)
{
	uint16_t ret;

	asm volatile ("inw %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}

uint32_t inl(uint16_t port)
{
	uint32_t ret;

	asm volatile ("inl %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}

void insl(uint16_t port, void *address, int count)
{
	asm volatile ("cld; rep insl" :
		      "=D" (address), "=c" (count) :
		      "d" (port), "0" (address), "1" (count) :
		      "memory", "cc");
}

void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" : : "a" (val), "Nd" (port));
}

void outw(uint16_t port, uint16_t val)
{
	asm volatile ("outw %0, %1" : : "a" (val), "Nd" (port));
}

void outl(uint16_t port, uint32_t val)
{
	asm volatile ("outl %0, %1" : : "a" (val), "Nd" (port));
}
