
#ifndef VIRTFS_H
#define VIRTFS_H

#include <stdint.h>
#include <stddef.h>
#include <kernel/device.h>
#include <kernel/dirent.h>
#include <kernel/types.h>
#include <kernel/fcntl.h>
#include <kernel/stat.h>

#define PATH_MAX_LENGTH			1024


struct file_descriptor {
	int 						fd_num;
	struct device* 				fd_dev;
	struct filesystem* 			fd_fs;
	ino_t 						inode;
	int 						fd_flags;
	uint32_t 					fd_position;
	uint32_t 					fd_closed;
	struct file_descriptor* 	fd_next;
};


struct vnode {
	char 						mnt_path[PATH_MAX_LENGTH];
	struct device* 				mnt_dev;
	struct filesystem* 			mnt_fs;
	struct vnode* 				subnodes;
};


struct filesystem {
	char 					fs_name[128];
	int (*delete)			(struct device* dev, const char* path);
	int (*write)			(struct device*, ino_t ino, const char* data, off_t off, size_t len);
	int (*read)				(struct device*, ino_t ino, char* data, off_t off, size_t len);
	int (*readdir) 			(struct device*, ino_t ino, int d, struct dirent* dent);
	int (*rename) 			(struct device*, ino_t ino, const char* name);
	int (*fstat) 			(struct device*, ino_t ino, struct stat* stat_struct);
	int (*open) 			(struct device*, const char* path, struct file_descriptor* fd);
	struct filesystem* 		next_fs;
};

void register_filesystem(struct filesystem* fs);
int mount(const char* path, const char* fs, struct device* dev);
struct vnode* vfs_getnode(const char* path);
void vfs_chroot(struct vnode* root);

#endif
