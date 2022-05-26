#include "lib.h"

int __toupper(int c)
{
    return ((c >= 65 && c <= 90) ? (c + 32) : c);
}
