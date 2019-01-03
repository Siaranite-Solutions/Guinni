#ifndef TIME_H
#define TIME_H

#include <kernel/types.h>

struct tm {
	int 		tm_sec;
	int 		tm_min;
	int 		tm_hour;
	int 		tm_mday;
	int 		tm_mon;
	int 		tm_year;
	int 		tm_wday;
	int 		tm_yday;
	int 		tm_isdst;
};

extern time_t time(time_t* timer);
extern struct tm* gmtime(const time_t *timep);
extern struct tm* gmtime_r(const time_t *timep, struct tm* buf);

#endif
