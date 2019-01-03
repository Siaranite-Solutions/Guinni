/*
 * pit.c
 * The Programmable Interrupt Timer (iirc)
 */

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <kernel/common.h>
#include <kernel/interrupt.h>
#include <kernel/types.h>
#include <kernel/memory/kheap.h>
#include <kernel/paging.h>
#include <kernel/process.h>
#include <kernel/kernel.h>

static void pit_irq(struct regs *state);


void init_pit(uint32_t freq)
{
	request_irq(0, pit_irq);
	uint32_t divisor = 1193180 / freq;
	outb(0x43, 0x36);
	outb(0x40, divisor & 0xFF);
	outb(0x40, (divisor >> 8) & 0xFF);
}

static void pit_irq(struct regs *state)
{
	perform_context_switch(state);
}
