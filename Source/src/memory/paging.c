/*
 * paging.c
 * The low level paging code, this really should never
 * be used. memmanager.h provides more abstraction, this
 * is basically the raw code for writing to page directories
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/memory/kheap.h>
#include <kernel/memory/paging.h>
#include <kernel/memory/memmanager.h>
#include <kernel/memory/page_fault.h>

#define IDENTITY_MAP_END                0x1E84800


bool paging_enabled;

struct page_directory *current_directory;

static struct page_directory *kernel_directory;

void page_alloc(struct page_directory *dir, uint32_t vaddr, uint32_t paddr, bool write, bool user)
{
	vaddr /= 0x1000;
	uint32_t i = vaddr / 1024;
	if (!dir->tables[i]) {
		dir->tables[i] = (struct page_table *)malloc_pa(sizeof(struct page_table));
		for (int x = 0; x < 0x1000; x++)
			((char *)dir->tables[i])[x] = 0;
		dir->tables_physical[i] = (uint32_t)dir->tables[i] | 0x7;
	}

	struct page *p = &dir->tables[i]->pages[vaddr % 1024];
	if (p->present)
		return;
	p->frame = paddr >> 12;
	p->present = 1;
	p->rw = write;
	p->user = user;
}


void page_remap(struct page_directory *dir, uint32_t vaddr, uint32_t paddr)
{
	vaddr /= 0x1000;
	uint32_t i = vaddr / 1024;
	void *old_t = dir->tables[i];
	dir->tables[i] = (struct page_directory *)malloc_pa(sizeof(struct page_table));
	memcpy(dir->tables[i], old_t, sizeof(struct page_table));
	dir->tables_physical[i] = (uint32_t)dir->tables[i] | 0x7;
	struct page *p = &dir->tables[i]->pages[vaddr % 1024];
	p->frame = paddr >> 12;
}


void page_free(struct page_directory *dir, uint32_t vaddr)
{
	vaddr /= 0x1000;
	uint32_t i = vaddr / 1024;
	memset(&dir->tables[i]->pages[vaddr % 1024], 0, sizeof(struct page));
}

struct page_directory *create_new_page_directory()
{
	struct page_directory *dir = (struct page_directory *)malloc_pa(sizeof(struct page_directory));

	memset(dir, 0, sizeof(struct page_directory));

	for (uint32_t ptr = 0; ptr < IDENTITY_MAP_END; ptr += 0x1000)
		page_alloc(dir, ptr, ptr, 0, 0);
	return dir;
}

/*
 * Initializes paging
 */
void init_paging()
{
	request_isr(14, page_fault_handler);

	kernel_directory = (struct page_directory *)malloc_pa(sizeof(struct page_directory));
	memset(kernel_directory, 0, sizeof(struct page_directory));

	switch_page_directory(kernel_directory);
	for (uint32_t ptr = 0; ptr < IDENTITY_MAP_END; ptr += 0x1000)
		page_alloc(kernel_directory, ptr, ptr, 0, 0);

	enable_paging();
}

/*
 * Switches the current page directory
 */
void switch_page_directory(struct page_directory *dir)
{
	current_directory = dir;
	asm volatile ("mov %0, %%cr3" :: "r" (&dir->tables_physical));
	asm volatile ("mov %cr3, %eax; mov %eax, %cr3;");
}


void disable_paging()
{
	paging_enabled = false;
	uint32_t cr0;
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 &= 0x7fffffff;
	asm volatile ("mov %0, %%cr0" :: "r" (cr0));
}

void enable_paging()
{
	paging_enabled = true;
	uint32_t cr0;
	asm volatile ("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	asm volatile ("mov %0, %%cr0" :: "r" (cr0));
}
