#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VEICULOS 5
#define NUM_PILHAS 3

typedef struct cel {
    char placa[9];
    struct cel *prox;
} veiculo;

typedef struct {
    int veiculos; /* Quantidade de veiculos estacionados */
    veiculo *topo; /* Topo da pilha */
} pilha;

typedef struct {
    char data[11];
    pilha P[NUM_PILHAS]; /* Armazena as pilhas P0, P1, ..., NUM_PILHAS-1 */
} estacionamento;

// funções base pilha
int empilha(pilha *p, const char *placa) {
    if (p->veiculos >= MAX_VEICULOS) {
        return 0;
    }
    veiculo *novo = (veiculo *)malloc(sizeof(veiculo));
    strcpy(novo->placa, placa);
    novo->prox = p->topo;
    p->topo = novo;
    p->veiculos++;
    return 1;
}

char *desempilha(pilha *p) {
    if (p->topo == NULL) {
        return NULL;
    }
    veiculo *removido = p->topo;
    char *placa = (char *)malloc(9);
    strcpy(placa, removido->placa);
    p->topo = removido->prox;
    p->veiculos--;
    free(removido);
    return placa;
}

void imprimirPilha(pilha *p, int indice) {
    printf("P%d:", indice);
    veiculo *atual = p->topo;
    int ultimo = 1;

    while (atual != NULL) {
        if (!ultimo) {
            printf(",");
        }
        printf("%s", atual->placa);
        atual = atual->prox;
        ultimo = 0;
    }
    printf("\n");
}


void limpaPilhas(pilha *p) {
    veiculo *atual = p->topo;
    while (atual != NULL) {
        veiculo *removido = atual;
        atual = atual->prox;
        free(removido);
    }
    p->topo = NULL;
    p->veiculos = 0;
}

void inicializaPilha(pilha *p) {
    p->veiculos = 0;
    p->topo = NULL;
}

void inicializaEstacionamento(estacionamento *est) {
    for (int i = 0; i < NUM_PILHAS; i++) {
        inicializaPilha(&est->P[i]);
    }
}

int menorPilha(estacionamento *est) {
    int i = 0;
    for (int j = 1; j < NUM_PILHAS; j++) {
        if (est->P[j].veiculos < est->P[i].veiculos) {
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
        inicializaEstacionamento(&est);

        scanf("%s", est.data);
        printf("%s\n", est.data);

        char operacao;
        int finalizar_dia = 0;

        while (finalizar_dia != 1) {
            scanf(" %c", &operacao);

            if (operacao == 'F') { // Finaliza o dia
                printf("F\n\n");
                for (int i = 0; i < NUM_PILHAS; i++) {
                    limpaPilhas(&est.P[i]);
                }
                finalizar_dia = 1;
            } else if (operacao == 'E') { // Entrada de veículo
                char placa[9];
                scanf("%s", placa);
                int indice = menorPilha(&est);
                if (empilha(&est.P[indice], placa)) {
                    printf("E %s\n", placa);
                } else {
                    printf("C %s\n", placa);
                }
            } else if (operacao == 'S') { // Saída de veículo
                char placa[9];
                scanf("%s", placa);
                int encontrado = 0;

                for (int i = 0; i < NUM_PILHAS; i++) {
                    pilha auxiliar = {0, NULL};

                    while (est.P[i].topo != NULL && !encontrado) {
                        char *atual = desempilha(&est.P[i]);
                        if (strcmp(atual, placa) == 0) {
                            printf("S %s\n", atual);
                            encontrado = 1;
                            free(atual);
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
                }

                if (!encontrado) {
                    printf("N %s\n", placa);
                }
            } else if (operacao == 'I') { // Imprime pilha
                char pilha_indice[3];
                scanf("%s", pilha_indice);
                int i = pilha_indice[1] - '0';
                imprimirPilha(&est.P[i], i);
            }
        }
    }
}

int main() {
    gerenciar_estacionamento();
    return 0;
}
