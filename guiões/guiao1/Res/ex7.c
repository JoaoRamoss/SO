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

//Print do nome e da idade do ultimo elemento a ser inserido ou atualizado.
int show_results (int fd, PESSOA p) {
    lseek(fd, -sizeof(struct pessoa), SEEK_CUR); //Coloca fd no inicio do struct.
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
    int pos = lseek(fd, 0, SEEK_END); //coloca fd no final do ficheiro para escrever la, e guarda essa posição.
    if (write(fd, &p, sizeof(struct pessoa)) < 0) { //Escreve o struct no ficheiro (a partir da posição pos).
        perror("Write Error");
        close(fd);
        return 1;
    }
    show_results(fd, p);
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
    if (isdigit(nome[0]) != 1) { //Verifica se deu o nome ou o endereço.
        while (read(fd, &aux, sizeof(struct pessoa)) > 0 && escrito != 1) {
            if (strcmp(aux.nome, nome) == 0) { //Procura pelo nome inserido.
                aux.idade = idade; //Atualiza idade
                lseek(fd, - sizeof(struct pessoa), SEEK_CUR); //Volta a colocar fd no inicio do struct.
                if (write(fd, &aux, sizeof(struct pessoa))  < 0) { //Escreve "por cima" com a idade atualizada.
                    perror("Write Error");
                    return 1;
                }
                escrito = 1; //Flag para interromper o ciclo.
            }
        }  
    }
    else {
        printf("A procurar endereço dado pelo utilizador...\n");
        lseek(fd, atoi(nome), SEEK_CUR); //Coloca fd no endereço inserido.
        if (read(fd, &aux, sizeof(struct pessoa)) < 0) { //Lê a partir desse endereço.
            perror("Read Error");
            close(fd);
            return 1;
        }
        aux.idade = idade; //Atualiza idade.
        lseek(fd, -sizeof(struct pessoa), SEEK_CUR); //Volta a colocar fd no inicio do struct.
        if (write(fd, &aux, sizeof(struct pessoa)) < 0) { //Escreve "por cima" com a idade atualizada.
            perror("Write error");
            close(fd);
            return 1;
        }
            escrito = 1; //Flag
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