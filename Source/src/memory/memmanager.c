/*
 * memmanager.c
 * The kernel memory manager, manages page frame
 * allocation
 */

#include <stdint.h>
#include <stddef.h>
#include <kernel/memory/paging.h>
#include <kernel/memory/memmanager.h>

extern struct page_directory *current_directory;

static struct page_frame *free_frame_stack = NULL;
static struct page_frame *allocated_frame_stack = NULL;

static void *phys_free_address = 0x1E84800;

static struct page_frame *pop_free_frame();

void *frame_alloc(void *vaddr, int flags)
{
	struct page_frame *frame = pop_free_frame();

	if (!frame) {
		frame = (struct page_frame *)kalloc(sizeof(struct page_frame));
		frame->phys_addr = phys_free_address;
		phys_free_address += 0x1000;
	}
	frame->ref_count = 1;
	page_alloc(current_directory, vaddr, frame->phys_addr, flags & 1, (flags & 2) >> 1);
	frame->virt_addr = (uint32_t)vaddr;
	frame->last_frame = allocated_frame_stack;
	frame->page_directory = current_directory;
	allocated_frame_stack = frame;
}

void frame_free(void *vaddr)
{
	vaddr = (uint32_t)vaddr;
	struct page_frame *curr = allocated_frame_stack;
	struct page_frame *prev = curr;
	while (curr) {
		if (curr->virt_addr == vaddr && curr->page_directory == current_directory) {
			curr->ref_count = 0;
			if (prev == curr)
				allocated_frame_stack = curr->last_frame;
			else
				prev->last_frame = curr->last_frame->last_frame = prev->last_frame;
			curr->last_frame = free_frame_stack;
			free_frame_stack = curr;
			page_free(current_directory, vaddr);
			return;
		}
		prev = curr;
		curr = curr->last_frame;
	}
}


static struct page_frame *pop_free_frame()
{
	struct page_frame *curr = free_frame_stack;

	if (!curr) {
		return NULL;
	} else {
		free_frame_stack = curr->last_frame;
		return curr;
	}
}
