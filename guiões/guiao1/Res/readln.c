#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define BUF_SIZE 1024
#define READ_BUF 512

char read_buffer[READ_BUF];
int read_buffer_pos = 0;
int read_buffer_end = 0;

int read_char (int fd, char *c) {
    if (read_buffer_pos == read_buffer_end) {
        read_buffer_end = read (fd, read_buffer, READ_BUF);

        switch (read_buffer_end){
        case -1:
            perror("read");
            return -1;
        case 0: 
            return 0;    
        default:
            read_buffer_pos = 0;
        }
    }
    *c = read_buffer[read_buffer_pos++];
    return 1;
}

//3 (Sem realloc, o tamanho do buffer / linha fica ao encargo da função que chama readln)
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

//4 (Not sure se era isto que era suposto fazer, mas funciona)
ssize_t readln_alt (int fd, char *line, size_t size) {
    ssize_t res = 0;
    int i = 0;
    while (i < size && (res = read_char(fd, &line[i])) > 0) {
        if (line[i] == '\n'){
            i += res;
            return i;
        }
        i += res;
    }
    return i;
}

int main (int argc, char *argv[]) {
    int read_bytes = 0, i = 1, written_bytes = 0;
    char *line = malloc(sizeof(char) * 1024);
    while ((read_bytes = readln_alt (STDIN_FILENO, line, 1024)) > 0) {
        printf("%d: ", i++);
        written_bytes += write(STDOUT_FILENO, line, read_bytes);
    }
    free(line);
    return 0;
}
