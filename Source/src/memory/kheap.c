#include <stddef.h>
#include <stdint.h>
#include <kernel/memory/kheap.h>


#define MAGIC           0x50BADA55
#define GUARD_1         0xCB0A0D0D
#define GUARD_2         0xCB05160E

/*
 * kheap.c
 * The kernel heap
 */


/*
 * NOTE: Remind myself to rewrite this, the current implemenation
 * uses a linked list which works; however finding a free block
 * is quite slow. If I use two seperate stacks (One for free blocks,
 * one for allocated blocks) speed should be that of O(1) (I think)
 */

struct mblock *mlist;                   // Heap linked list

void *freeaddress;                      // The next free address

static void *kheap_alloc(size_t size);
static struct mblock *kheap_get_block(size_t size);

/*
 * Initiliazes the kernel heap using a custom placement address
 */
void init_kheap(uint32_t i)
{
	freeaddress = ((int)i % 8) + i;
	mlist = NULL;
}



void *kalloc(size_t size)
{
	struct mblock *new_block = kheap_get_block(size);

	if (new_block->state == MBLOCK_ALLOCATED)
		new_block->memory = kheap_alloc(size);
	else
		new_block->state = MBLOCK_ALLOCATED;
	return new_block->memory;
}

/*
 * Allocates memory in the kernel heap
 */
static void *kheap_alloc(size_t size)
{
	size_t real_size = size + (size % 8) + 8;

	void *address = freeaddress;

	freeaddress += real_size;
	*((int *)address) = GUARD_1;
	*((int *)(address + real_size - 4)) = GUARD_2;
	return address + 4;
}


static struct mblock *kheap_get_block(size_t size)
{
	size = size + (size % 8);
	struct mblock *i = mlist;
	struct mblock *last = i;
	struct mblock *ret = NULL;
	uint32_t smallest = -1;
	while (i) {
		if (i->size >= size && i->size < smallest && i->state == MBLOCK_FREE) {
			smallest = i->size;
			ret = i;
		}
		last = i;
		i = i->next_block;
	}
	if (ret) {
		return ret;
	} else {
		struct mblock *new_block = (struct mblock *)kheap_alloc(sizeof(struct mblock));
		new_block->size = size;
		new_block->magic = MAGIC;
		new_block->state = MBLOCK_ALLOCATED;
		new_block->next_block = NULL;
		if (mlist == NULL)
			mlist = new_block;
		else
			last->next_block = new_block;
		return new_block;
	}
}
/*
 * Reallocates an existing block of memory, with
 * a new size
 */
void *realloc(void *ptr, size_t size)
{
	size_t org = ksize(ptr);

	kfree(ptr);
	void *ret_val = kalloc(size);
	memcpy(ret_val, ptr, org);
	return ret_val;
}

/*
 * Allocates a block of memory, returns page aligned
 * address
 */
void *malloc_pa(size_t size)
{
	void *old_free = freeaddress;

	freeaddress = ((uint32_t)freeaddress & 0xFFFFF000) + 0x1000;

	void *ret = freeaddress;
	freeaddress += size;
	return ret;
}

static int lck = 0;
/*
 * Frees a block of memory
 */
void kfree(void *ptr)
{
	struct mblock *fb = mlist;

	while (fb != NULL) {
		if (ptr >= fb->memory && ptr < fb->memory + fb->size && fb->state == MBLOCK_ALLOCATED) {
			if (*((int *)(fb->memory - 4)) != GUARD_1 || *((int *)(fb->memory + fb->size)) != GUARD_2)
				panic("kernel heap corruption!");
			fb->state = MBLOCK_FREE;
			return;
		}
		fb = fb->next_block;
	}
}

/*
 * Gets the size of a block of memory
 */
size_t ksize(void *ptr)
{
	struct mblock *fb = mlist;

	while (fb) {
		if (ptr >= fb->memory && ptr < fb->memory + fb->size && fb->state == MBLOCK_ALLOCATED)
			return fb->size;
		fb = fb->next_block;
	}
	return 0;
}
