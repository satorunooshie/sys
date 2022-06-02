#include "lib.h"

size_t __strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
    char *d = dst;
    const char *s = src;
    size_t n = dstsize;
    size_t dlen;
    while (n-- != 0 && *d != '\0')
        d++;
    dlen = d - dst;
    n = dstsize - dlen;
    if (!n)
        return (dlen + __strlen(s));
    while (*s)
    {
        if (n != 1)
        {
            *d++ = *s;
            n--;
        }
        s++;
    }
    *d = '\0';
    return (dlen + (s - src));
}
