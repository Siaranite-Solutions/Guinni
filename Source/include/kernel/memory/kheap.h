#ifndef KHEAP_H
#define KHEAP_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
	MBLOCK_ALLOCATED = 0,
	MBLOCK_FREE = 1
} memorystate_t;

struct mblock {
	uint32_t 			magic;
	memorystate_t 		state;
	void* 				memory;
	size_t 				size;
	void* 				next_block;
};

extern void init_kheap(uint32_t i);
extern void* kalloc(size_t s);
extern void* malloc_pa(size_t s);
extern void* realloc(void* ptr, size_t size);
extern void kfree(void* ptr);
extern size_t ksize(void* ptr);

#endif
