#include "lib.h"

int __isalnum(int c)
{
    return (__isalpha(c) || __isdigit(c));
}
