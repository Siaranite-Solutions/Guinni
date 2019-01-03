#include <stdint.h>
#include <stddef.h>
#include <kernel/device.h>
#include <kernel/common.h>
#include <kernel/tty.h>
#include <kernel/ringbuffer.h>
#include <kernel/kernel.h>
#include <kernel/time.h>

extern struct device textscreen_device;

static struct device *printk_output = &textscreen_device;
static int should_log_messages = 1;
static struct ring_buffer msg_queue;

static void kernel_log_msg(kernelmsg_t *msg);

void printk(const char *format, ...)
{
	va_list argp;

	va_start(argp, format);
	char tmp_buff[512];
	memset(tmp_buff, 0, 512);
	vsprintf(tmp_buff, format, argp);
	va_end(argp);
	if (should_log_messages) {
		kernelmsg_t msg;
		memcpy(&msg.msg_string, tmp_buff, 512);
		gmtime_r(time(NULL), &msg.msg_tm);
		kernel_log_msg(&msg);
	}
	if (printk_output)
		printk_output->write(tmp_buff, strlen(tmp_buff), 0);
}

void klog(int log)
{
	if (log)
		rb_init(&msg_queue, sizeof(kernelmsg_t) * 256);
	should_log_messages = log;
}

void klog_output(struct device *dev)
{
	printk_output = dev;
}

static void kernel_log_msg(kernelmsg_t *msg)
{
	rb_push(&msg_queue, msg, sizeof(kernelmsg_t));
}
