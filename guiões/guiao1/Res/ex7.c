#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#define BUF_SIZE 1024

typedef struct pessoa {
    int idade; 
    char nome[100];
}PESSOA;

int insert (char *ficheiro, PESSOA p, char *nome, int idade) {
    printf("Modo de insercao...\n");
    int fd = open (ficheiro, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Open Error");
        return 1;
    }
    p.idade = idade;
    strcpy(p.nome, nome);
    int pos = lseek(fd, 0, SEEK_END);
    if (write(fd, &p, sizeof(struct pessoa)) < 1) {
        perror("Write Error");
        close(fd);
        return 1;
    }
    printf("Guardado na posicao: %d\n", pos);
    close(fd);
    return 0;
}

int update (char *ficheiro,char *nome, int idade) {
    printf("Modo de atualizacao...\n");
    int fd = open (ficheiro, O_RDWR);
    int escrito = 0;
    if (fd < 0) {
        perror("Open Error");
        return 1;
    }
    PESSOA aux;
    if (isdigit(nome[0]) != 1) {
        while (read(fd, &aux, sizeof(struct pessoa)) > 0 && escrito != 1) {
            if (strcmp(aux.nome, nome) == 0) {
                aux.idade = idade;
                lseek(fd, - sizeof(struct pessoa), SEEK_CUR);
                if (write(fd, &aux, sizeof(struct pessoa))  < 0) {
                    perror("Write Error");
                    return 1;
                }
                escrito = 1;
            }
        }  
    }
    else {
        lseek(fd, atoi(nome), SEEK_CUR);
        if (read(fd, &aux, sizeof(struct pessoa)) < 0) {
            perror("Read Error");
            close(fd);
            return 1;
        }
        lseek(fd, -sizeof(struct pessoa), SEEK_CUR);
        if (write(fd, &aux, sizeof(struct pessoa)) < 0) {
            perror("Write error");
            close(fd);
            return 1;
        }
            escrito = 1;
    }
    if (escrito == 1){
        close(fd);
        return 0;
    }
    return 1;
}

int main (int argc, char *argv[]) {
    PESSOA p;
    if (argc < 5) {
        printf("Erro: Nao foram inseridos argumentos suficientes na linha de comandos.\n");
        return 0;
    }
    
    if ((*(argv[2] + 1) == 'i') && argc == 5) {
        if (insert (argv[1], p, argv[3], atoi(argv[4])) == 0)
            printf("Inserido com sucesso.\n");
    }

    if ((*(argv[2] + 1) == 'u') && argc == 5) {
        if (update(argv[1], argv[3], atoi(argv[4])) == 0) 
            printf("Dados atualizados com sucesso.\n");
    }

}