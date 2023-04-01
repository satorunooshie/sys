#include <stdio.h>
#include <stdlib.h>

static void cat(FILE *f);

int main(int argc, char *argv[])
{
    int i;

    if (argc == 1) {
        cat(stdin);
        exit(0);
    }
    for (i = 1; i < argc; i++) {
        FILE *f;
        f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            exit(1);
        }
        cat(f);
        fclose(f);
    }
    exit(0);
}

static void cat(FILE *f)
{
    int c;

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
