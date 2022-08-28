#include "lib.h"

char *__strstr(const char *haystack, const char *needle)
{
    char c, sc;
    size_t l;
    if ((c = *needle++) != 0) {
        l = __strlen(needle);
        do {
            do {
                if ((sc = *haystack++) == 0)
                    return (NULL);
            } while (sc != c);
        } while (__strncmp(haystack, needle, l) != 0);
        haystack--;
    }
    return ((char*)haystack);
}
