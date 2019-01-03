/*
 * sched.c
 * The scheduler, handles multitasking and process
 * creation
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
#include <kernel/pit.h>

extern struct page_directory *current_directory;

struct process *current_process = NULL;

static struct process *proc_queue;

static char scheduler_enabled = 1;

void init_sched()
{
	struct process *nproc = kalloc(sizeof(struct process));

	nproc->next_proc = NULL;
	nproc->pid = 0;
	nproc->image.stack_base = malloc_pa(0x10000);
	nproc->register_context.useresp = nproc->image.stack_base + 0x10000;
	nproc->image.page_directory = current_directory;
	set_kernel_stack(kalloc(0xA0000) + 0xA0000);
	proc_queue = nproc;
	current_process = nproc;
	init_pit(100);
	asm ("sti");
	for (int i = 0; i < 10; i++)
		asm ("hlt");
}


void perform_context_switch(struct regs *state)
{
	static int first_switch = 1;

	if (scheduler_enabled) {
		memcpy(&current_process->register_context, state, sizeof(struct regs));
		current_process->image.page_directory = current_directory;
		current_process = current_process->next_proc;
		if (!current_process)
			current_process = proc_queue;
		if (first_switch) {
			current_process->image.stack_base = state->esp - 0x1000;
			first_switch = 0;
		}
		memcpy(state, &current_process->register_context, sizeof(struct regs));

		switch_page_directory(current_process->image.page_directory);
	}
}

void schedule_process(struct process *proc)
{
	struct process *plist = proc_queue;

	proc->image.kernel_stack = kalloc(0x10000);
	proc->register_context.esp = proc->image.kernel_stack + 0x10000;
	while (plist->next_proc != NULL) plist = plist->next_proc;
	plist->next_proc = proc;
}

void scheduler_enable()
{
	scheduler_enabled = 1;
}

void scheduler_disable()
{
	scheduler_enabled = 0;
}
