#include "lib.h"

char *__strchr(const char *s, int c)
{
    while (++s) {
        if (*s == c) return ((char *)s);
        if (!*s) break ;
    }
    return ((char *)NULL);
}
