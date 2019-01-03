#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/common.h>
#include <kernel/vga.h>
#include <kernel/device.h>

struct device textscreen_device;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const vram = (uint16_t*) 0xB8000;
static int pos;
int foreground_color;
int background_color;

static void terminal_newline()
{
	if (pos % 80 == 0) {
		pos += 80;
		return;
	}
	while (pos % 80 != 0)
		pos++;
}

static void textscreen_scroll()
{
	memcpy(vram, vram + 80, (80 * 25) - 80);
	for (int i = 80; i < (80 * 25); i++)
		vram[i - 80] = vram[i];
	for (int i = 0; i < 80; i++)
		vram[((80 * 25) - 80) + i] = 0;
	pos = (80 * 25) - 80;
}

void terminal_initialize(void) {
	set_attributes(15, 0);
	clrscr();
	textscreen_device.device_name = "textscreen";
	textscreen_device.device_type = DEV_CHAR_DEVICE;
	textscreen_device.write = terminal_write;
	register_device(&textscreen_device);
}

void clrscr()
{
	for (int i = 0; i < 2000; i++)
		vram[i] = 0;
	pos = 0;
}

void set_attributes(char fg, char bg)
{
	foreground_color = fg;
	background_color = bg;
}

void terminal_putchar(const char c)
{
	if (c == '\n') {
		terminal_newline();
	} else if (c == '\b') {
		pos--;
		terminal_putchar(' ');
		pos--;
	} else {
		if (pos >= 2000)
			textscreen_scroll();
		int attr = (((background_color) << 4) | (foreground_color & 0x0F)) << 8;
		vram[pos++] = c | attr;
	}
}


void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
