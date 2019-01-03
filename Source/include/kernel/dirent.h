#ifndef DIRENT_H
#define DIRENT_H

#include <kernel/types.h>

typedef struct {
    int 				dd_fd;
    int 				dd_loc;	
    int 				dd_seek;
    char* 				dd_buf;
    int 				dd_len;
    int 				dd_size; 
} DIR;

struct dirent
{   
	ino_t 				d_ino;
	off_t 				d_off;
	unsigned short int 	d_reclen;
	unsigned char 		d_type;
	char 				d_name[256];
};

DIR* opendir(const char *name);
DIR* fdopendir(int fd);
struct dirent* readdir(DIR* dir);
#endif
