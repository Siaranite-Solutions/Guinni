/*
 * page_fault.c
 * Handles page faults
 */

#include <stdint.h>
#include <stddef.h>
#include <kernel/interrupt.h>
#include <kernel/types.h>
#include <kernel/process.h>
#include <kernel/sched.h>
#include <kernel/kernel.h>


extern struct process *current_process;

void page_fault_handler(struct regs *regs)
{
	caddr_t fault;

	asm volatile ("mov %%cr2, %0" : "=r" (fault));

	if (current_process) {
		/*
		 * Relax! No need to fear, this address belongs to the process
		 * but it just hasn't been paged so we need to allocate the page
		 * and return
		 */
		if (fault < current_process->image.image_brk && fault >= current_process->image.image_base) {
			frame_alloc(fault & 0xFFFFF000, 2);
			return;
		}
	}

	panic("page fault at 0x%p", fault);
}
