#ifndef STAT_H
#define STAT_H

#include <kernel/types.h>

struct stat {
  unsigned short 		st_dev;
  unsigned short 		st_ino;
  unsigned int 			st_mode;
  unsigned short 		st_nlink;
  unsigned short 		st_uid;
  unsigned short 		st_gid;
  unsigned short 		st_rdev;
  unsigned int 			st_size;
  unsigned int 			st_atime;
  unsigned int 			st_mtime;
  unsigned int 			st_ctime;
};

int fstat(int fd, struct stat* buf);

#endif
