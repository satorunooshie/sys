#include "lib.h"

size_t __strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
    char *d = dst;
    const char *s = src;
    size_t n = dstsize;
    if (n) {
        while (--n) {
            if ((*d++ = *s++) == '\0')
                break ;
        }
    }
    if (!n) {
        if (dstsize)
            *d = '\0';
        while (*s++)
            ;
    }
    return (s - src - 1);
}
