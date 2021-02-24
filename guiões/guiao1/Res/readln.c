#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

//Nao percebi bem o objetivo do parametro size
//Nota: apenas funciona se a linha nao exceder 1024 bytes.
//Exercicio 3
ssize_t readln (int fd, char *line, size_t size) {
    int i = 0;
    char t = 0;
    ssize_t tam = 0, res = 0;;
   do {
        tam = read(fd, &t, 1);
        if (t != '\n') {
            line[i++] = t;
            res++;
        }
        else 
            break;
    } while (tam != 0);
    return res;
}

int main (int argc, char *argv[]) {
    char *line = malloc(sizeof(char) * 1024);
    int fd_read = open(argv[1], O_RDONLY);
    ssize_t tamanho_read = readln(fd_read, line, sizeof(char));
    printf("%s\n", line);
    close(fd_read);
}