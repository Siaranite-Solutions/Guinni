#ifndef PAGE_FAULT_H
#define PAGE_FAULT_H

#include <stdint.h>
#include <kernel/interrupt.h>

extern void page_fault_handler(struct regs* regs);

#endif
