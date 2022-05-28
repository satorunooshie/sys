#include "lib.h"

char *__strdup(const char *s1)
{
    char *str;
    size_t l;

    l = __strlen(s1) + 1;
    str = (char*)malloc(sizeof(char) * l);
    if (!str)
        return NULL;
    __strcpy(str, s1);
    return (str);
}
