#include "lib.h"

char *__strrchr(const char *s, int c)
{
    char *res;
    res = NULL;
    while (1) {
        if (*s == c) res = (char *)s;
        if (!*s) break ;
        s++;
    }
    return (res);
}
