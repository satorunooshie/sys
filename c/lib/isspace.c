#include "lib.h"

int __isspace(int c)
{
    // (9 <= c && c <= 13) || c == 32)
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == 'r' || c == '\12');
}
