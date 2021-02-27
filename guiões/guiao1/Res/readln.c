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
    ssize_t tam = 0, res = 0;;
   do {
       if (i == size-1) {
           size *= 2;
           line = realloc(line, sizeof(char)*size);
       }
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

//4 (Not sure se era isto que era suposto fazer, mas funciona).
ssize_t readln_alt (int fd, char *line, size_t size) {
    int k = 0;
    char t = 0, aux[10];
    ssize_t tam = 0, res = 0;
    do {
        int i = 0, flag = 0;
        tam = read(fd, aux, 10);
        if (k == size-1) {
            size *= 2;
            line = realloc(line, sizeof(char)*size);
        }

        for (i = 0; i < 10; i++){
            if (aux[i] == '\n') {
                flag = 1;
                break;
            }
        }
    if (flag == 0) {
        for (int j = 0; j < 10; line[k++] = aux[j++], res++);
    }
    else {
        for (int j = 0; j < i; line[k++] = aux[j++], res++);
        break;
    }
        
    }while (tam != 0);
    return res;
}

int main (int argc, char *argv[]) {
    char *line = malloc(sizeof(char) * 1024);
    int fd_read = open(argv[1], O_RDONLY);
    ssize_t tamanho_read = readln(fd_read, line, sizeof(char)*1024);
    printf("%s\n", line);
    close(fd_read);
}