/*
 * irq.c
 * Provides a simple interface for kernel level drivers
 * to request IRQ handlers
 */

#include <stdint.h>
#include <stddef.h>
#include <kernel/interrupt.h>

inthandler_t irq_handlers[16];

int request_irq(int inum, inthandler_t handler)
{
	if (inum > 16 || irq_handlers[inum])
		return -1;
	else
		irq_handlers[inum] = handler;
	return 0;
}

int free_irq(int inum)
{
	irq_handlers[inum] = NULL;
	return 0;
}

void handle_irq(struct regs registers)
{
	int i = registers.interrupt & 0xFF;

	if (i >= 40)
		outb(0xA0, 0x20);
	if (irq_handlers[i - 32])
		irq_handlers[i - 32](&registers);
	outb(0x20, 0x20);
}
