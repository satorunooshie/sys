#include "lib.h"

int __atoi(const char *str)
{
    signed int sum = 0;
    unsigned int isminus = 0;

    if (*str == '+') str++;
    else if (*str == '-') {
        isminus = 1;
        str++;
    }
    while (*str != '\0' && *str >= '0' && *str <= '9') {
        sum += *str - '0';
        sum *= 10;
        str++;
    }
    if (isminus) sum = 0 - sum;
    return sum / 10;
}
