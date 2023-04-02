#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void cat(FILE *f, int escape);

static struct option longopts[] = {
    {"escape", no_argument, NULL, 'e'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
    int opt;
    int escape = 0;

    while ((opt = getopt_long(argc, argv, "e", longopts, NULL)) != -1) {
        switch (opt) {
            case 'e':
                escape = 1;
                break;
            case 'h':
                fprintf(stdout, "Usage: %s [-e] [FILE ...]\n", argv[0]);
                exit(0);
            case '?':
                fprintf(stderr, "Usage: %s [-e] [FILE ...]\n", argv[0]);
                exit(1);
        }
    }

    argc -= optind;
    argv += optind;
    if (argc == 0) cat(stdin, escape);
    else {
        int i;
        for (i = 0; i < argc; i++) {
            FILE *f;
            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            cat(f, escape);
            fclose(f);
        }
    }
    exit(0);
}

static void cat(FILE *f, int escape)
{
    int c;

    if (escape) {
        while ((c = fgetc(f)) != EOF) {
            switch (c) {
                case '\t':
                    if (fputs("\\t", stdout) == EOF) exit(1);
                    break;
                case '\n':
                    if (fputs("$\n", stdout) == EOF) exit(1);
                    break;
                default:
                    if (putchar(c) < 0) exit(1);
                    break;
            }
        }
        return;
    }
    while ((c = fgetc(f)) != EOF) if (putchar(c) < 0) exit(1);
}

//static void __cat(const char *path) 
//{
//    int fd;
//    unsigned char buf[BUFFER_SIZE];
//    int n;
//
//    fd = open(path, O_RDONLY);
//    if (fd < 0) die(path);
//    for (;;) {
//        n = read(fd, buf, sizeof buf);
//        if (n < 0) die(path);
//        if (n == 0) break;
//        if (write(STDOUT_FILENO, buf, n) < 0) die(path);
//    }
//    if (close(fd < 0)) die(path);
//}

//static void die(const char *s)
//{
//    perror(s);
//    exit(1);
//}
