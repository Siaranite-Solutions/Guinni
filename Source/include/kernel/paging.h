#ifndef PAGING_H
#define PAGING_H

#include <stdbool.h>
#include <stdint.h>

struct page
{
	uint32_t 			present    : 1;
	uint32_t 			rw         : 1;
	uint32_t 			user       : 1;
	uint32_t 			accessed   : 1;
	uint32_t 			dirty      : 1;
	uint32_t 			unused     : 7;
	uint32_t 			frame      : 20;
} __attribute__((packed));

struct page_table
{
	struct page 		pages[1024];
};

struct page_directory
{  
	struct page_table* 	tables[1024];
	uint32_t 			tables_physical[1024];
	uint32_t 			physical_addr;
};


extern void init_paging();
extern void switch_page_directory(struct page_directory* dir);
extern void enable_paging();
extern void disable_paging();
extern void page_alloc(struct page_directory* dir, uint32_t vaddr, uint32_t paddr, bool write, bool user);
extern void page_remap(struct page_directory* dir, uint32_t vaddr, uint32_t paddr);
extern void page_free(struct page_directory* dir, uint32_t vaddr);
extern struct page_directory* create_new_page_directory();

#endif
