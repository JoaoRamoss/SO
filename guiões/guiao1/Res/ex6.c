#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

struct test {
    int i;
    char n[10];
};

int main (int argc, char *argv[]) {
    int fd = open(argv[1], O_CREAT | O_TRUNC | O_RDONLY, 0644);

    if (fd < 0) {
        perror("Open error: ");
        return 1;
    }

    struct test t1;
    t1.i = 10;
    strcpy(t1.n, "22");

    struct test t2;
    t2.i = 4;
    strcpy(t2.n, "pp");

    write(fd, &t1, sizeof(struct test));
    write(fd, &t2, sizeof(struct test));
    lseek(fd, 0, SEEK_SET);

    struct test res;
    int read_bytes = 0;

    read_bytes = read(fd, &res, sizeof(struct test));

    char output[100];
    sprintf(output, "%d\n", res.i);
    write(1, res.n, strlen(output));
    write(1, "-", 1);
    write(1, output, srtrlen(output));

    close(fd);
}