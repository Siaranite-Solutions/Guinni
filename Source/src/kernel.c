//#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/gdt.h>


void kernel_main(void) {
	terminal_initialize();
	terminal_writestring("Initializing GDT\n");
	init_gdt();
	terminal_writestring("Initializing IDT\n");
	init_idt();
	terminal_writestring("Hello, kernel World!\n");
}
