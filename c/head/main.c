#include <stdio.h>
#include <stdlib.h>

static void head(FILE *f, long nlines);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(1);
    }
    head(stdin, atol(argv[1]));
    exit(0);
}

static void head(FILE *f, long nlines)
{
    int c;

    if (nlines <= 0) return;
    while ((c = getc(f)) != EOF) {
        if (putchar(c) < 0) exit(1);
        if (c == '\n') if (--nlines == 0) return;
    }
}
