#include "lib.h"

int __isprint(int c)
{
    return ((c >= 32) && (c <= 126));
}
