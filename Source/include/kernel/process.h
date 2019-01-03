#ifndef PROCESS_H
#define PROCESS_H


#include <kernel/types.h>
#include <kernel/memory/paging.h>
#include <kernel/interrupt.h>
#include <kernel/virtfs.h>

struct process_image;
struct process;

struct process_image
{
	void* 					sig_handlers[256];
	struct page_directory* 	page_directory;
	uid_t 					uid;
	gid_t 					gid;
	uint32_t 				kernel_stack;
	uint32_t 				stack_base;
	uint32_t 				image_base;
	uint32_t 				image_brk;
	uint32_t 				paged;
	struct process_image* 	next_image;
	
};

struct process
{
	pid_t 					pid;
	pid_t 					parent_pid;
	struct process_image 	image;
	struct file_descriptor* file_descriptors;
	struct regs 			register_context;
	struct process* 		next_proc;

};


extern pid_t fork();
#endif
