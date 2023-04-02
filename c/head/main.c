#include <stdio.h>
#include <stdlib.h>

static void head(FILE *f, long nlines);

int main(int argc, char *argv[])
{
    long nlines;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s n [file file...]\n", argv[0]);
        exit(1);
    }
    nlines = atoi(argv[1]);
    if (argc == 2) head(stdin, nlines);
    else {
        int i;
        for (i = 2; i < argc; i++) {
            FILE *f;
            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            head(f, nlines);
            fclose(f);
        }
    }
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
