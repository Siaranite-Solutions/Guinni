/*
 * ringbuffer.c
 * Implemenation of a ring buffer datastructure
 */

#include <kernel/sync.h>
#include <kernel/ringbuffer.h>
#include <kernel/memory/kheap.h>

static void rb_push_byte(struct ring_buffer *rb, char b);
static int rb_pop_byte(struct ring_buffer *rb);

void rb_init(struct ring_buffer *rb, int size)
{
	rb->rb_len = size;
	rb->rb_pos = 0;
	rb->rb_buff = kalloc(size);
	spin_unlock(&rb->rb_lock);
}

void rb_push(struct ring_buffer *rb, const void *data, int len)
{
	spin_lock(&rb->rb_lock);
	for (int i = 0; i < len; i++)
		rb_push_byte(rb, ((char *)data)[i]);
	spin_unlock(&rb->rb_lock);
}

void rb_pop(struct ring_buffer *rb, void *buf, int len)
{
	spin_lock(&rb->rb_lock);
	for (int i = len - 1; i >= 0; i--)
		((char *)buf)[i] = (char)rb_pop_byte(rb);
	spin_unlock(&rb->rb_lock);
}

static void rb_push_byte(struct ring_buffer *rb, char b)
{
	rb->rb_buff[rb->rb_pos % rb->rb_len] = b;
	rb->rb_pos++;
}

static int rb_pop_byte(struct ring_buffer *rb)
{
	rb->rb_pos--;
	int ret = rb->rb_buff[rb->rb_pos % rb->rb_len];
	return ret;
}
