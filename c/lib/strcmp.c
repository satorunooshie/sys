#include "lib.h"

int __strcmp(const char *s1, const char *s2)
{
    signed int res;
    res = 0;
    while (1)
    {
        res = *s1 - *s2++;
        if (res != 0 || !*s1++)
            break ;
    }
    return (res);
}
