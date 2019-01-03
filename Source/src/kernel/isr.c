/*
 * isr.c
 * Provides a simple interface for kernel level drivers
 * to request ISR handlers
 */

#include <stdint.h>
#include <stddef.h>
#include <kernel/interrupt.h>

inthandler_t isr_handlers[256];

int request_isr(int inum, inthandler_t handler)
{
	if (isr_handlers[inum])
		return -1;
	else
		isr_handlers[inum] = handler;
	return 0;
}

int free_isr(int inum)
{
	isr_handlers[inum] = NULL;
	return 0;
}

void handle_isr(struct regs registers)
{
	int i = registers.interrupt & 0xFF;

	if (isr_handlers[i])
		isr_handlers[i](&registers);
	outb(0x20, 0x20);
}
