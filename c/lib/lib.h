#ifndef LIB_H
#define LIB_H

#include <stddef.h>
#include <stdlib.h>

// <ctype.h>
int __isalnum(int c);
int __isalpha(int c);
int __isdigit(int c);
int __islower(int c);
int __isprint(int c);
int __isspace(int c);
int __isupper(int c);
int __tolower(int c);
int __toupper(int c);

// <stdlib.h>
int __atoi(const char *str);

// <string.h>
char *__strcat(char *restrict s1, const char *restrict s2);
char *__strchr(const char *s, int c);
char *__strcpy(char *dst, const char *src);
char *__strdup(const char *s1);
char *__strncat(char *restrict s1, const char *restrict s2, size_t n);
char *__strncpy(char *dst, const char *src, size_t len);
char *__strstr(const char *haystack, const char *needle);
int __strcmp(const char *s1, const char *s2);
int __strncmp(const char *s1, const char *s2, size_t n);
size_t __strlcat(char *restrict dst, const char *restrict src, size_t dstsize);
size_t __strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
size_t __strlen(const char *s);

#endif
