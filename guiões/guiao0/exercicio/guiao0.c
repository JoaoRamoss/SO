//ESCREVER "MAKE" NO TERMINAL PARA COMPILAÇÃO DO PROGRAMA
//EXERCICIO 1 e 2
#include <stdio.h>
#include <stdlib.h>
#include "aux_guiao0.h"
#define TAM 10

//variavel global
int v2[TAM];

int main () {
    //Variavel local
    int v[TAM];

    //Variavel dinamica
    int *v3 = calloc(TAM, sizeof(int));

    //PARA VARIAVEIS LOCAIS:
    fill(v, TAM, 1);
    printf("Variavel local:\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", v[i]);
    }
    printf("\nFind (%d): %d\n", 1, find(v, TAM, 1));

    //VARIAVEIS GLOBAIS:
    fill(v2, TAM, 3);
    printf("Variavel global:\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", v2[i]);
    }
    printf("\nFind (%d): %d\n", 7, find(v2, TAM, 7));

    //VARIAVEIS DINAMICAS
    fill(v3, TAM, 5);
    printf("Variavel dinamica:\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", v3[i]);
    }
    printf("\nFind (%d): %d\n", 1, find(v3, TAM, 1));
    free(v3);
    //Conclusao: Todos os tipos de definição do array funcionam com a API.
}

//EXERCICIO 3
/*

Ao redefinirmos a funcao find como find(int* vector, int size, int begin, int end, int size);
poderiamos alterar a função de modo a que a procura seja feita na janela entre "begin" e "end", incluindo
uma variavel com o tamanho total do array, de modo a nos certificarmos de que este tamanho nunca é excedido.

*/

//EXERCICIO 4
/*

Se tentarmos preencher alguma posição que excede o tamanho do array (i.e. tentar preencher v[12] quando v esta 
definido como int v[10];), o programa vai dar um erro do tipo "segmentation fault", o que impede a execução do mesmo.
Por esta razão, deveremos sempre certficar-nos de que nao acedemos a mais memória do que aquela que reservámos.

*/