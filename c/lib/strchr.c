#include "lib.h"

char *__strchr(const char *s, int c)
{
    while (1) {
        if (*s == c) return ((char *)s);
        if (!*s) break ;
        s++;
    }
    return ((char *)NULL);
}
