#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_entry {
	uint16_t 		limit_low;
	uint16_t		base_low;
	uint8_t 		base_middle;      
	uint8_t 		access; 
	uint8_t 		granularity;
	uint8_t 		base_high;         
} __attribute__((packed));

struct gdt_ptr
{
	uint16_t 		limit;
	uint32_t		base;
}  __attribute__((packed));


extern void init_gdt();
extern void gdt_flush(uint32_t ptr);
extern void set_kernel_stack(uint32_t stack);
#endif
