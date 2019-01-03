#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include <stdint.h>

#define PAGE_RW			0x01
#define PAGE_USER		0x02

struct page_frame;

struct page_frame
{
	uint16_t 				ref_count;
	uint32_t 				phys_addr;
	uint32_t 				virt_addr;
	uint32_t 				index;
	struct page_frame* 		last_frame;
	struct page_directory* 	page_directory;
};

void* frame_alloc(void* vaddr, int flags);
void* frame_alloc_d(struct page_directory* dir, void* vaddr, int flags);
void frame_free(void* vaddr);
void* frame_free_d(struct page_directory* dir, void* vaddr);
void* frame_map(void* vaddr, void* freeaddr);

#endif
