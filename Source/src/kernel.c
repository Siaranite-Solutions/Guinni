//#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/idt.h>
#include <kernel/gdt.h>

#include <kernel/stat.h>
#include <kernel/dirent.h>
#include <kernel/time.h>
#include <kernel/ringbuffer.h>

#include <kernel/interrupt.h>
#include <kernel/device.h>
#include <kernel/memory/kheap.h>
#include <kernel/paging.h>

#include <mboot.h>

extern struct device textscreen_device;

static void run_init();
static void cpu_idle();

void kernel_main(multiboot_info_t *mbootinfo)
{
	klog(1);
	terminal_initialize();
	printk("Initializing GDT\n");
	init_gdt();
	printk("Initializing IDT\n");
	init_idt();
	printk("GUINNI > Hello, kernel World!\n");
	printk("Initializing kernel heap...\n");
	init_kheap(*(uint32_t *)(mbootinfo->mods_addr + 4));
	printk("Initialized kernel heap!\n");
	printk("Initializing memory paging...\n");
	init_paging();
	printk("Initialized memory paging!\n");
	printk("Initializing scheduler...\n");
	init_sched();
	printk("Initialized scheduler!\n");


	run_init();
}

static void run_init()
{
	pid_t pid = fork();

	if (pid)
		panic("could not start init");
	else
		cpu_idle();
}

static void cpu_idle()
{
	while (1)
		asm ("hlt");
}
