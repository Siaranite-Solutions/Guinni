#ifndef FCNTL_H
#define FCNTL_H

#include <kernel/virtfs.h>
#include <kernel/device.h>
#include <kernel/types.h>

/* Modes for open */
#define	O_RDONLY	0x0000
#define	O_WRONLY	0x0001
#define	O_RDWR		0x0002
#define	O_CREAT		0x0200
#define	O_TRUNC		0x0400

/* Commands for fcntl */
#define	F_DUPFD		0
#define	F_GETFD		1
#define	F_SETFD		2
#define	F_GETFL		3
#define	F_SETFL		4



extern int fcntl(int fd, int cmd, ...);
extern int open(const char* path, int flags);
extern int close(int fd);
extern size_t read(int fd, void* buf, size_t nbytes);
extern size_t write(int _fd, const void* buf, size_t nbytes);

#endif
