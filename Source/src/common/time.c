/*
 * time.c
 * Implements several methods found in time.h
 * Note: the implemention of time() is found in
 * hardware/rtc.c
 */

#include <stdint.h>
#include <stddef.h>
#include <kernel/types.h>
#include <kernel/time.h>


struct tm *gmtime(const time_t *timep)
{
}

struct tm *gmtime_r(const time_t *timep, struct tm *buf)
{
	time_t t = time(NULL);

	buf->tm_hour = (t / 3600) % 24;
	buf->tm_min = (t / 60) % 60;
	buf->tm_sec = t % 60;
	return buf;
}
