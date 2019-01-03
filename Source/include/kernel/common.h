#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

extern int strlen(const char* str);
extern char* strrchr (const char* str, char ch);
extern char* strlchr (const char* str, char ch);
extern char* strcpy (char * dest, const char* src);
extern char* strncpy (char* dest, const char* src, size_t len);
extern int strncmp(const char* str1, const char* str2, size_t len);
extern int strcmp(const char* str1, const char* str2);
extern char* strcat(char* dest, const char* dat);
extern char* strncat(char* dest, const char* dat, size_t dlen);
extern void reverse(char* rv);
extern void itoa(char* s,int i);
extern int atoi(char* s);
extern void itox(char* s, unsigned int i);
extern void vsprintf(char* dest, const char* format, va_list argp);
extern void sprintf(char* dest, const char* format, ...);
extern int strindx (const char* str, char ch);
extern int strtol(char* s, int base);
extern void* memcpy(void* dest, void* src, size_t size);
extern void* memset(void* source, uint8_t b, size_t size);

#endif
