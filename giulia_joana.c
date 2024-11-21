/**************************************************
*
* Giulia Delarissa e Joana Maria Cunha Costa
* Trabalho 2
* Professor(a): Diego Rupert
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VEICULOS 5
#define NUM_PILHAS 3


/* Armazena informacoes de um veiculo estacionado em uma pilha */
typedef struct cel
{
    char placa[9];
    struct cel *prox;
} veiculo;

/* Armazena informacoes de uma pilha */
typedef struct
{
    int veiculos; /* Quantidade de veiculos estacionados */
    veiculo *topo; /* Topo da pilha */
} pilha;

/* Armazena informacoes do estacionamento */
typedef struct
{
    char data[11];
    pilha P[NUM_PILHAS]; /* Armazena as pilhas P0, P1, ..., NUM_PILHAS-1 */
} estacionamento;

// funções base pilha

//criar empilha, desempilha, imprimePilha e limpaPilhas
//empilha
//desempilha
//imprimePilha
//limpaPilhas
void inicializaPilha(pilha *p) {
    p->veiculos = 0;
    p->topo = NULL;
}

// controle do estacionamento

void inicializaEstacionamento(estacionamento *est) {
    for (int i = 0; i < NUM_PILHAS; i++) {
        inicializaPilha(&est->P[i]);
    }
}

int menorPilha(estacionamento *est) {
    int i = 0;
    for (int j = 1; j < NUM_PILHAS; j++) {
        if (est->P[i].veiculos < est->P[i].veiculos) {
            i = j;
        }
    }
    return i;
}

void gerenciar_estacionamento() {
    int c;
    scanf("%d", &c);

    for (int i = 0; i < c; i++) {
        estacionamento est;
        inicializar_pilhas(&est);

        scanf("%s", est.data);
        printf("%s\n", est.data);

        char operacao;

        while (1) {
            scanf(" %c", &operacao);

            if (operacao == 'F') { // Finaliza o dia
                printf("F\n\n");
                // criar uma funcao que apaga o conteudo das pilhas e add aqui
            } else if (operacao == 'E') { // Entrada de veículo
                char placa[9];
                scanf("%s", placa);
                int indice = menorPilha(&est);
                if (empilha(&est.P[indice], placa)) {
                    printf("E %s\n", placa); // Sucesso
                } else {
                    printf("C %s\n", placa); // Estacionamento cheio
                }
            } else if (operacao == 'S') { // Saída de veículo
                char placa[9];
                scanf("%s", placa);
                int encontrado = 0;

                for (int i = 0; i < NUM_PILHAS; i++) {
                    pilha auxiliar = {0, NULL};

                    while (est.P[i].topo != NULL) {
                        char *atual = desempilha(&est.P[i]);
                        if (strcmp(atual, placa) == 0) {
                            printf("S %s\n", atual); // Veículo removido
                            encontrado = 1;
                            free(atual);
                            break;
                        } else {
                            empilha(&auxiliar, atual);
                            free(atual);
                        }
                    }

                    while (auxiliar.topo != NULL) {
                        char *atual = desempilha(&auxiliar);
                        empilha(&est.P[i], atual);
                        free(atual);
                    }

                    if (encontrado) break;
                }

                if (!encontrado) {
                    printf("N %s\n", placa); // Veículo não encontrado
                }
            } else if (operacao == 'I') {
                int i;
                scanf("%d", &i);
                imprimirPilha(&est.P[i], i); // Impressão de pilha
            }
        }
    }
}

int main()
{
    gerenciar_estacionamento();
}
