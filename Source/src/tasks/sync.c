/*
 * sync.c
 * Provides methods for basic thread synchronization
 */

#include <kernel/types.h>

void spin_lock(spinlock_t *lock)
{
	while (*lock) ;
	*lock = 1;
}

void spin_unlock(spinlock_t *lock)
{
	*lock = 0;
}

void mutex_lock(mutex_t *lock)
{
	while (*lock) asm ("hlt");
	*lock = 1;
}

void mutex_unlock(mutex_t *lock)
{
	*lock = 0;
}
