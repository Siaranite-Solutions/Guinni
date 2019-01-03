#ifndef SYNC_H
#define SYNC_H

#include <kernel/types.h>

extern void spin_lock(spinlock_t* lock);
extern void spin_unlock(spinlock_t* lock);
extern void mutex_lock(mutex_t* lock);
extern void mutex_unlock(mutex_t* lock);

#endif
