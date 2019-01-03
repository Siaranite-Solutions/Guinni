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

extern struct page_directory *current_directory;
extern struct process *current_process;
static uint32_t next_pid = 1;

static void create_stack(uint32_t org_stack, struct page_directory *dir)
{
	void *new_stack = malloc_pa(0x10000);

	memcpy(new_stack, org_stack, 0x10000);
	for (int i = 0; i < 0x10000; i += 0x1000)
		page_remap(dir, org_stack + i, new_stack + i);
}

pid_t fork()
{
	struct process *nproc = kalloc(sizeof(struct process));

	memcpy(nproc, current_process, sizeof(struct process));
	struct page_directory *pdir = (struct page_directory *)malloc_pa(sizeof(struct page_directory));
	memcpy(pdir, current_directory, sizeof(struct page_directory));

	create_stack(nproc->image.stack_base, pdir);

	nproc->image.page_directory = pdir;
	nproc->next_proc = NULL;
	nproc->register_context.eip = __builtin_return_address(0);
	nproc->register_context.eax = next_pid;
	nproc->pid = next_pid++;
	schedule_process(nproc);

	return 0;
}
