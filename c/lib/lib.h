#ifndef LIB_H
#define LIB_H

#include <stddef.h>

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

// <string.h>
size_t __strlen(const char *s);

#endif
