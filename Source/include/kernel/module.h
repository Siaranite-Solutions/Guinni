#ifndef MODULE_H
#define MODULE_H


#include <stdint.h>

#define MODULE_MAGIC	0xCB01180E

typedef int (*mod_init_t)();
typedef int (*mod_uninit_t)();

struct module
{
	uint32_t 			mod_magic;
	char 				mod_name[128];
	mod_init_t 			mod_init;
	mod_uninit_t 		mod_uninit;
	struct module* 		next_module;
};

#endif
