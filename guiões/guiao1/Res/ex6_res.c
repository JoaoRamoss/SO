#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#define BUF_SIZE 1024

typedef struct pessoa {
    int idade; 
    char nome[BUF_SIZE];
}PESSOA;

void insert (int fd, PESSOA p, char *nome, int idade) {
    p.idade = idade;
    strcpy(p.nome, nome);
    write(fd, &p, sizeof(PESSOA));
}


int main (int argc, char *argv[]) {
    int fd = open (argv[1], O_CREAT | O_TRUNC | O_RDONLY, 0644);
    if (fd < 0) {
        perror("Open Error: ");
        return 1;
    }
    PESSOA p;

    if (strcmp(argv[2], "-i")) {
        insert (fd, p, argv[3], atoi(argv[4]));
        lseek(fd, 0, SEEK_SET);
    }

}