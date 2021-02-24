#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#define BUFFER_SIZE 1024

int main (int argc, char *argv[]) {

    ssize_t read_bytes = 0;
    ssize_t written_bytes = 0;

    char *buffer = malloc(sizeof(char) * 1024);

    while ((read_bytes = read (STDIN_FILENO, buffer, 1024)) > 0) {
        written_bytes += write(STDOUT_FILENO, buffer, read_bytes);
    }
    free(buffer);
    return 0;
}