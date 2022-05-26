#include "lib.h"

int __isalpha(int c)
{
    return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
