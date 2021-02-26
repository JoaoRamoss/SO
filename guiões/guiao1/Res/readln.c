#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//3
ssize_t readln (int fd, char *line, size_t size) {
    int i = 0;
    char t = 0;
    ssize_t tam = 0;
   do {
       if (i == size-1) {
           size *= 2;
           line = realloc(line, sizeof(char)*size);
       }
        tam = read(fd, &t, 1);
        if (t != '\n')
            line[i++] = t;
        else 
            break;
    } while (tam != 0);
    return i;
}

int main (int argc, char *argv[]) {
    char *line = malloc(sizeof(char) * 1024);
    int fd_read = open(argv[1], O_RDONLY);
    ssize_t tamanho_read = readln(fd_read, line, sizeof(char)*1024);
    printf("%s\n", line);
    close(fd_read);
}