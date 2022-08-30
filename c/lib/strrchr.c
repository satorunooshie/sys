#include "lib.h"

char *__strrchr(const char *s, int c)
{
    char *res;
    res = NULL;
    while (*s) {
        if (*s == c) res = (char *)s;
        s++;
    }
    return (res);
}
