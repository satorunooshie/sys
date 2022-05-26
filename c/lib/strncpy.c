#include "lib.h"

char *__strncpy(char *dst, const char *src, size_t len)
{
    size_t l;
    l = -1;
    while (*src != '\0' && ++l < len)
        *dst++ = *src++;
    *dst = '\0';
    return (dst);
}
