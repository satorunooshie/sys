#include "lib.h"

char *__strncat(char *restrict s1, const char *restrict s2, size_t n)
{
    char *tmp;
    tmp = s1;
    while (*s1)
        s1++;
    while ((*s1++ = *s2++) != '\0' && n--)
        ;
    return (tmp);
}
