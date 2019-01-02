/*
 * string.c
 * Provides a simple implemenation of most standard
 * string functions for the kernel to use
 */

#include <stddef.h>
#include <stdarg.h>
#include <kernel/common.h>

int strlen(const char *str)
{
	int i = 0;

	while (str[i] != 0) i++;
	return i;
}

char *strrchr(const char *str, char ch)
{
	int dlen = strlen(str);

	for (int i = 0; i < dlen; i++)
		if ((char *)str[i] == ch)
			return (char *)(str + i);
	return NULL;
}

char *strlchr(const char *str, char ch)
{
	int dlen = strlen(str);
	char *rstr = NULL;

	for (int i = 0; i < dlen; i++)
		if ((char *)str[i] == ch)
			rstr = (char *)(str + i);
	return rstr;
}

int strindx(const char *str, char ch)
{
	int dlen = strlen(str);
	char *rstr = NULL;

	for (int i = 0; i < dlen; i++)
		if ((char *)str[i] == ch)
			return i;
	return -1;
}
char *strcpy(char *dest, const char *src)
{
	size_t len = strlen(src);

	for (int i = 0; i < len; i = i + 1)
		dest[i] = src[i];
	dest[len] = 0;
	return dest;
}

char *strncpy(char *dest, const char *src, size_t len)
{
	for (int i = 0; i < len && dest[i] != NULL; i++)
		dest[i] = src[i];
	return dest;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	for (int i = 0; i < len; i++)
		if (str1[i] != str2[i])
			return -1;
	return 0;
}

int strcmp(const char *str1, const char *str2)
{
	if (strlen(str1) > strlen(str2))
		return strncmp(str1, str2, strlen(str1));
	else
		return strncmp(str1, str2, strlen(str2));
}

char *strcat(char *dest, const char *dat)
{
	int dlen = strlen(dat);

	strncat(dest, dat, dlen);
	return dest;
}

char *strncat(char *dest, const char *dat, size_t dlen)
{
	int pos = 0;

	while (dest[pos] != 0) pos++;
	char *new_str = (char *)(dest + pos);
	for (int i = 0; i < dlen; i = i + 1)
		new_str[i] = dat[i];
	return dest;
}

void reverse(char *str)
{
	int start = 0;
	int end = strlen(str) - 1;

	while (start < end) {
		char c1 = *(str + start);
		char c2 = *(str + end);
		*(str + start) = c2;
		*(str + end) = c1;
		start++;
		end--;
	}
}

void itoa(char *s, int i)
{
	int d;
	int p = 0;

	do {
		d = i % 10;
		i = (i - d) / 10;
		s[p] = (char)d + 48;
		p = p + 1;
	} while (i > 0);
	s[p] = 0;
	reverse(s);
}

int atoi(char *s)
{
	int final = 0;
	int mul = 1;
	int len = strlen(s);

	reverse(s);
	for (int i = 0; i < len; i++) {
		char b = s[i];
		int RealDigit = (int)b - 48;
		final = (RealDigit * mul) + final;
		mul = mul * 10;
	}
	return final;
}

int strtol(char *s, int base)
{
	int final = 0;
	int mul = 1;
	int len = strlen(s);

	//reverse(s);
	for (int i = (len - 1); i >= 0; i--) {
		char b = s[i];
		int RealDigit;
		if (b >= 'a')
			RealDigit = 10 + ((int)b - 'a');
		else
			RealDigit = (int)b - 48;
		final = (RealDigit * mul) + final;
		mul = mul * base;
	}
	return final;
}
void itox(char *s, unsigned int i)
{
	int d;
	int p = 0;

	do {
		d = i % 16;
		i = (i - d) / 16;
		s[p++] = (char)d + (d < 10 ? 48 : 'A' - 10);
	} while (i > 0);
	reverse(s);
	s[p] = 0;
}

void vsprintf(char *dest, const char *format, va_list argp)
{
	int len = strlen(format);
	int ptr = 0;
	char nbuf[16];

	for (int i = 0; i < len; i++) {
		char *c = format[i];
		if (c == '%') {
			char spec = format[++i];
			switch (spec) {
			case '%':
				dest[ptr++] = '%';
				break;
			case 's':
				strcpy((char *)(dest + ptr), va_arg(argp, char *));
				ptr = strlen(dest);
				break;
			case 'd':
				itoa(nbuf, va_arg(argp, int));
				strcpy((char *)(dest + ptr), nbuf);
				dest += strlen(nbuf);
				break;
			case 'x':
				itox(nbuf, va_arg(argp, int));
				strcpy((char *)(dest + ptr), nbuf);
				dest += strlen(nbuf);
				break;
			case 'p':
				memset(nbuf, 0, 16);
				memset(nbuf, '0', 8);
				itox(nbuf, va_arg(argp, int));
				strcpy((char *)(dest + ptr), nbuf);
				nbuf[8] = 0;
				dest += 8;
				break;
			case 'c':
				dest[ptr++] = va_arg(argp, int);
				break;
			default:

				break;
			}
		} else {
			dest[ptr++] = c;
		}
	}
}



