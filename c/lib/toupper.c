#include "lib.h"

int __toupper(int c)
{
    return ((c >= 97 && c <= 122) ? (c - 32) : c);
}
