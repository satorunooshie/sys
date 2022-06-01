#include "lib.h"

char *__strcat(char *restrict s1, const char *restrict s2)
{
    char *tmp;
    tmp = s1;
    while (*s1)
        s1++;
    while ((*s1++ = *s2++) != '\0')
        ;
    return (tmp);
}
