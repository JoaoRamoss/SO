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

int show_results (int fd, PESSOA p) {
    lseek(fd, -sizeof(struct pessoa), SEEK_CUR);
    if (read(fd, &p, sizeof(struct pessoa)) < 0) {
        perror("Read error na leitura");
        return 1;
    }
    char output [100];
    sprintf(output, "%d\n", p.idade);
    write (STDOUT_FILENO, "Nome: ", 6);
    write(STDOUT_FILENO, p.nome, strlen(p.nome));
    write(STDOUT_FILENO, "\nIdade: ", 8);
    write(STDOUT_FILENO, output, strlen(output));
    return 0;
}

int insert (char *ficheiro, PESSOA p, char *nome, int idade) {
    printf("Modo de insercao...\n");
    int fd = open (ficheiro, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Open Error");
        return 1;
    }
    p.idade = idade;
    strcpy(p.nome, nome);
    lseek(fd, 0, SEEK_END);
    if (write(fd, &p, sizeof(struct pessoa)) < 1) {
        perror("Write Error");
        close(fd);
        return 1;
    }
    show_results(fd, p);
    close(fd);
    return 0;
}

int update (char *ficheiro,char *nome, int idade) {
    printf("Modo de atualizacao...\n");
    int fd = open (ficheiro, O_RDWR);
    int escrito = 0;
    if (fd < 0) {
        perror("Open Error");
        close(fd);
        return 1;
    }
    PESSOA aux;
    while (read(fd, &aux, sizeof(struct pessoa)) > 0 && escrito != 1) {
        if (strcmp(aux.nome, nome) == 0) {
            aux.idade = idade;
            lseek(fd, - sizeof(struct pessoa), SEEK_CUR);
            if (write(fd, &aux, sizeof(struct pessoa))  < 0) {
                perror("Write Error");
                close(fd);
                return 1;
            }
            escrito = 1;
        }
    }
    show_results(fd, aux);
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