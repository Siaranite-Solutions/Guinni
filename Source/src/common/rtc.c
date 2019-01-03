#include <stdint.h>
#include <stddef.h>
#include <kernel/types.h>
#include <kernel/portio.h>
#include <kernel/time.h>

#define CONVERT_TO_BINARY(x)     (((x & 0xF0) >> 1) + ((x & 0xF0) >> 3) + (x & 0xf))

#define RTC_SECONDS                     0x00
#define RTC_MINUTES                     0x02
#define RTC_HOURS                       0x04
#define RTC_WEEKDAY                     0x06
#define RTC_DAY_OF_MONTH        0x07
#define RTC_MONTH                       0x08
#define RTC_YEAR                        0x09
#define RTC_STATUS_A            0x0A
#define RTC_STATUS_B            0x0B


static uint16_t cmos_read(uint8_t cmos_reg);
static void cmos_write(uint8_t cmos_reg, uint8_t val);

static uint16_t cmos_read(uint8_t cmos_reg)
{
	outb(0x70, (0x80 << 7) | (cmos_reg));

	return inb(0x71);
}

static void cmos_write(uint8_t cmos_reg, uint8_t val)
{
	outb(0x70, (0x80 << 7) | (cmos_reg));

	outb(0x71, val);
}

void init_rtc()
{
}

time_t time(time_t *timer)
{
	int MONTH_LOOKUP[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int MONTH_LOOKUP_LEAP[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year = CONVERT_TO_BINARY(cmos_read(RTC_YEAR)) + 2000;
	int utime = CONVERT_TO_BINARY(cmos_read(RTC_SECONDS));

	for (int i = 0; i < CONVERT_TO_BINARY(cmos_read(RTC_MONTH)); i++)
		utime += MONTH_LOOKUP[i] * 86400;
	utime += CONVERT_TO_BINARY(cmos_read(RTC_MINUTES)) * 60;
	utime += CONVERT_TO_BINARY(cmos_read(RTC_HOURS)) * 3600;
	utime += CONVERT_TO_BINARY(cmos_read(RTC_DAY_OF_MONTH)) * 86400;
	utime += (year - 1970) * 31536000;
	if (timer)
		*timer = utime;
	return utime;
}
