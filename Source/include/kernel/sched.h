#ifndef SCHED_H
#define SCHED_H

#include <kernel/process.h>
#include <kernel/interrupt.h>

void init_sched();
void perform_context_switch(struct regs* context);
void schedule_process(struct process* proc);
void scheduler_enable();
void scheduler_disable();

#endif
