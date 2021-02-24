#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
#define BUFFER_SIZE 1024 //Quanto menos o buffer size maior o tempo de execução

int main (int argc, char *argv[]) {
    int fd_read = open (argv[1],O_RONLY);
    int fd_write = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0600);
    ssize_t read_bytes = 0;
    ssize_t written_bytes = 0;

    char *buffer = malloc(sizeof(char) * 1024);

    while (read_bytes = read (fd_read, buffer, 1024) > 0) {
        written_bytes += write(fd_write, buffer, read_bytes);
    }
    close(fd_read);
    close(fd_write);

    free(buffer);
}