#ifndef DEVICE_H
#define DEVICE_H

#include <stddef.h>
#include <stdint.h>

struct device;

typedef enum 
{
	DEV_BLOCK_DEVICE = 0,
	DEV_CHAR_DEVICE = 1,
} devtype_t;

struct device
{
	devtype_t 				device_type;
	char* 					device_name;
	size_t (*read) 			(char* buffer, size_t, uint32_t addr);
	size_t (*write) 		(const char* data, size_t, uint32_t add);
	struct device* 			next_device;
};

struct device* get_device_by_name(const char* dev);
void register_device(struct device* dev);

#endif
