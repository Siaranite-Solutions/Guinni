#ifndef KERNEL_H
#define KERNEL_H

#include <kernel/time.h>
#include <kernel/device.h>
#include <kernel/module.h>

typedef struct kernelmsg kernelmsg_t;

struct kernelmsg {
	struct tm			msg_tm;
	char 				msg_string[512];
	struct kernelmsg* 	last_msg;
};

extern void klog(int log);
extern void klog_output(struct device* dev);
extern void printk(const char* format, ...);
extern void panic(const char* format, ...);
extern void shutdown();
extern int insert_module(struct module* mod);
extern int init_module(struct module* mod);
#endif
