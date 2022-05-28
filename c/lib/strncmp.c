#include "lib.h"

int __strncmp(const char *s1, const char *s2, size_t n)
{
    signed char res;
    res = 0;
    while (n--)
    {
        res = *s1 - *s2++;
        if (res != 0 || !*s1++)
            break ;
    }
    return (res);
}
