#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <kernel/common.h>
#include <kernel/tty.h>
#include <kernel/interrupt.h>
#include <kernel/kernel.h>

extern struct device textscreen_device;

static void display_registers(struct regs *regs);

void panic(const char *format, ...)
{
	//klog_output(&textscreen_device);


	/*
	 * The kernel log is useless at this point so disable it
	 */
	//klog(0);

	char msg_buff[512];
	va_list argp;
	va_start(argp, format);
	vsprintf(msg_buff, format, argp);
	va_end(argp);

	printk("kernel panic: %s\n\n", msg_buff);
	printk("The system is HALTED!\n\0");


	while (1) ;
}
