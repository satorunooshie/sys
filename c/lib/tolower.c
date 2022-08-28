#include "lib.h"

int __tolower(int c)
{
    return ((c >= 65 && c <= 90) ? (c + 32) : c);
}
