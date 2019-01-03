
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <kernel/sync.h>

struct ring_buffer {
    char* 		rb_buff;
    int 		rb_len;
    int 		rb_pos;
    spinlock_t	rb_lock;
};


extern void rb_init(struct ring_buffer* rb, int size);
extern void rb_push(struct ring_buffer* rb, const void* data, int len);
extern void rb_pop(struct ring_buffer* rb, void* buf, int len);

#endif
