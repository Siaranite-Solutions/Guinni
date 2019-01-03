/*
 * device.c
 * Provides an abstraction layer for char/block devices
 */

#include <stddef.h>
#include <kernel/memory/kheap.h>
#include <kernel/device.h>

struct device *device_list = NULL;

void register_device(struct device *dev)
{
	dev->next_device = NULL;
	if (!device_list) {
		device_list = dev;
	} else {
		struct device *curr = device_list;
		while (curr->next_device)
			curr = curr->next_device;
		curr->next_device = dev;
	}
}


struct device *get_device_by_name(const char *dev)
{
	struct device *curr = device_list;

	while (curr->next_device)
		curr = curr->next_device;
	return NULL;
}
