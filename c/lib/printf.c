#include "lib.h"
#include <unistd.h>
#include <stdarg.h>

typedef struct s_args
{
    int c;
    int width;
    int has_width;
    int precision;
    int has_precision;
} t_args;

void __new_args(t_args *args)
{
    args->c = 0;
    args->width = 0;
    args->has_width = 0;
    args->precision = 0;
    args->has_precision = 0;
}

int __get_digits(int d)
{
    int digits = (d < 0) ? 1 : 0;

    if (d == 0)
        return (1);
    if (d == -2147483648)
        return (11);
    if (d < 0)
        d *= -1;
    while (d)
    {
        d /= 10;
        digits++;
    }
    return (digits);
}

int test_get_digits(int d)
{
    switch (d)
    {
        case 0:
            return (1);
        case -2147483648:
            return (11);
        case 2147483647:
            return (10);
        case -123:
            return (4);
        case 123:
            return (3);
        default:
            return (-1);
    }
}

int __get_digits_x(unsigned int ud)
{
    int digits = 0;

    while (ud)
    {
        ud /= 16;
        digits++;
    }
    return (digits);
}

int __putchar(int c)
{
    return write(1, &c, 1);
}

int __put_str(const char *s)
{
    if (!s)
        return (0);
    return write(1, s, __strlen(s));
}

int __put_strl(const char *s, int len)
{
    if (!s)
        return (0);
    return write(1, s, (len < __strlen(s)) ? len : __strlen(s));
}

int __puts(t_args *args, va_list ap)
{
    int res = 0;
    int width = args->width ? args->width : 0;
    int precision = args->has_precision ? args->precision : 0;
    char *s = va_arg(ap, char *);
    int len = 0;

    if (!s)
        s = "(null)";
    len = __strlen(s);
    len = (args->has_precision && precision < len) ? precision : len;
    while (width > len)
    {
        res += __putchar(' ');
        width--;
    }
    return (res + __put_strl(s, len));
}

int __put_i(int d, int padding)
{
    int res = 0;

    if (d == -2147483648)
    {
        res += __putchar('-');
        while (padding--)
            res += __putchar('0');
        return (res + __put_str("2147483648"));
    }
    if (d < 0)
    {
        res += __putchar('-');
        d *= -1;
    }
    while (padding--)
        res += __putchar('0');
    if (d >= 10)
        res += __put_i(d / 10, 0);
    return (res + __putchar(d % 10 + '0'));
}

int __put_x(unsigned int ud, int padding)
{
    int res = 0;

    while (padding--)
        res += __putchar('0');
    if (ud == 0)
        return (res);
    if (ud >= 16)
        res += __put_x(ud / 16, 0);
    if (ud % 16 < 10)
        res += __putchar(ud % 16 + '0');
    else
        res += __putchar(ud % 16 - 10 + 'a');
    return (res);
}

int __putd(t_args *args, va_list ap)
{
    int res = 0;
    int width = args->width ? args->width : 0;
    int precision = args->has_precision ? args->precision : 0;
    int d = va_arg(ap, int);
    int len = __get_digits(d);
    int padding = (d < 0) ? (precision > len - 1) ? precision - (len - 1) : 0 : (precision > len) ? precision - len : 0;

    // exception case for 0.
    if (d == 0 && args->has_precision && args->precision == 0)
        len = 0;
    len += padding;
    while (width > len)
    {
        res += __putchar(' ');
        width--;
    }
    // exception case for 0.
    if (d == 0 && args->has_precision && args->precision == 0)
        return (res);
    return (res + __put_i(d, padding));
}

int __putx(t_args *args, va_list ap)
{
    int res = 0;
    int width = args->width ? args->width : 0;
    int precision = args->has_precision ? args->precision : 0;
    int d = va_arg(ap, int);
    int len = __get_digits_x(d);
    int padding = (precision > len) ? precision - len : 0;

    // exception case for 0.
    if (d == 0 && args->has_precision && args->precision == 0)
        len = 0;
    len += padding;
    while (width > len)
    {
        res += __putchar(' ');
        width--;
    }
    // exception case for 0.
    if (d == 0 && args->has_precision && args->precision == 0)
        return (res);
    return (res + __put_x(d, padding));
}

int __put_conv(t_args *args, va_list ap)
{
    switch (args->c)
    {
    case '%':
        return __putchar('%');
    case 'd':
        return __putd(args, ap);
    case 's':
        return __puts(args, ap);
    case 'x':
        return __putx(args, ap);
    default:
        return (0);
    }
}

char *__read_args(t_args *args, char *itr)
{
    if (!itr || *itr != '%')
        return (itr);
    itr++;
    while (*itr)
    {
        __new_args(args);
        if (__isdigit(*itr))
        {
            args->has_width = 1;
            args->width = __atoi(itr);
            itr += __get_digits(args->width);
        }
        if (*itr == '.')
        {
            args->has_precision = 1;
            itr++;
            if (__isdigit(*itr))
            {
                args->precision = __atoi(itr);
                itr += __get_digits(args->precision);
            }
        }
        if (__strchr("dsx", *itr))
        {
            args->c = *itr;
            itr++;
            return (itr);
        }
    }
    return (itr);
}

int __printf(const char *restrict format, ...)
{
    char *itr = (char *)format;
    int res = 0;
    t_args args;
    va_list ap;

    itr = (char *)format;
    if (!itr)
        return (0);
    va_start(ap, format);
    while (*itr)
    {
        if (*itr == '%')
        {
            itr = __read_args(&args, itr);
            res += __put_conv(&args, ap);
            continue;
        }
        res += __putchar(*itr);
        itr++;
    }
    va_end(ap);
    return (res);
}

#ifdef TEST
#include <stdio.h>
#include <stdlib.h>
#define get_digits(d) test_get_digits(d)
#else
#define printf(format, ...) __printf(format, __VA_ARGS__)
#define atoi(str) __atoi(str)
#define get_digits(d) __get_digits(d)
#endif

int main()
{
    printf("%d\n", get_digits(-2147483648)); // 11
    printf("%d\n", get_digits(2147483647));  // 10
    printf("%d\n", get_digits(0));           // 1
    printf("%d\n", get_digits(-123));        // 4
    printf("%d\n", get_digits(123));         // 3

    printf("%d\n", atoi("-2147483648"));
    printf("%d\n", atoi("2147483648"));
    printf("%d\n", atoi("2147483647"));
    printf("%d\n", atoi("0"));

    printf("[%s]\n", "Hello World!");
    printf("[%s]\n", "hoge!");
    printf("[%10.5s]\n", "hoge!");
    printf("[%10.2s]\n", "hoge!");
    printf("[%10.0s]\n", "hoge!");
    printf("[%3.2s]\n", "hoge!");
    printf("[%3.10s]\n", "hoge!");
    printf("[%s]\n", NULL);
    printf("[%10.2s]\n", NULL);
    printf("[%10.0s]\n", NULL);
    printf("[%3.2s]\n", NULL);
    printf("[%3.10s]\n", NULL);

    printf("[%10.20d]\n", 0);
    printf("[%10.1d]\n", 0);
    printf("[%10.5d]\n", 0);
    printf("[%10.d]\n", 0);
    printf("[%10.5d]\n", 123);
    printf("[%10.5d]\n", -123);
    printf("[%.5d]\n", 123);
    printf("[%.5d]\n", -123);
    printf("[%10.5d]\n", 2147483647);
    printf("[%10.5d]\n", -2147483648);
    printf("[%10.d]\n", 2147483647);
    printf("[%10.d]\n", -2147483648);

    printf("[%10.1x]\n", 0);
    printf("[%10.x]\n", 0);
    printf("[%10.5x]\n", 123);
    printf("[%10.5x]\n", -123);
    printf("[%.5x]\n", 123);
    printf("[%.5x]\n", -123);
    printf("[%10.5x]\n", 2147483647);
    printf("[%10.5x]\n", -2147483648);
    printf("[%10.x]\n", 2147483647);
    printf("[%10.x]\n", -2147483648);
    return (0);
}
