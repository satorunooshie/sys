#include "lib.h"

char *__strcpy(char *dst, const char *src)
{
    int i;
    i = -1;
    while (src[++i] != '\0')
        dst[i] = src[i];
    dst[i] = '\0';
    return (dst);
}
