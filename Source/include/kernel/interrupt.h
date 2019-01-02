#ifndef INTERRUPT_H
#define INTERRUPT_H

struct regs
{
	uint32_t 		ds;                  
	uint32_t 		edi;
	uint32_t 		esi;
	uint32_t 		ebp;
	uint32_t 		esp;
	uint32_t 		ebx;
	uint32_t 		edx;
	uint32_t 		ecx;
	uint32_t 		eax; 
	uint32_t 		interrupt;
	uint32_t 		err_code;    
	uint32_t 		eip;
	uint32_t 		cs;
	uint32_t 		eflags;
	uint32_t 		useresp;
	uint32_t 		ss;
}; 

typedef void (*inthandler_t)(struct regs* registers);

int request_isr(int inum, inthandler_t handler);
int free_isr(int inum);

int request_irq(int inum, inthandler_t handler);
int free_irq(int inum);

#endif
