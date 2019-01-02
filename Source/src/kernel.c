//#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/gdt.h>


void kernel_main(void) {
	init_gdt();
	init_idt();
	terminal_initialize();
	terminal_writestring("Hello, kernel World!");
}
