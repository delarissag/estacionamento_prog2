#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEICULOS 5
#define NUM_PILHAS 3

typedef struct cel {
    char placa[9];
    struct cel *prox;
} veiculo;

typedef struct {
    int veiculos;
    veiculo *topo;
} pilha;

typedef struct {
    veiculo *inicio;
    veiculo *fim;
} fila;

typedef struct {
    char data[11];
    pilha P[NUM_PILHAS];
} estacionamento;

// funcoes auxiliares pilha
void inicializaPilha(pilha *p) {
    p->veiculos = 0;
    p->topo = NULL;
}

int empilha(pilha *p, char *placa) {
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
    if (p->veiculos == 0) {
        return NULL;
    }
    veiculo *removido = p->topo;
    p->topo = removido->prox;
    p->veiculos--;
    char *placa = (char *)malloc(9 * sizeof(char));
    strcpy(placa, removido->placa);
    free(removido);
    return placa;
}

void imprimirPilha(pilha *p, int indice) {
    printf("P%d:", indice);
    veiculo *atual = p->topo;
    if (atual != NULL) {
        while (atual != NULL) {
            printf("%s", atual->placa);
            if (atual->prox != NULL) {
                printf(",");
            }
            atual = atual->prox;
        }
    }
    printf("\n");
}

// funcoes auxiliares fila

void inicializaFila(fila *f) {
    f->inicio = f->fim = NULL;
}

void enfileira(fila *f, char *placa) {
    veiculo *novo = (veiculo *)malloc(sizeof(veiculo));
    strcpy(novo->placa, placa);
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    }
    f->fim = novo;

    if (f->inicio == NULL) {
        f->inicio = novo;
    }
}

char *desenfileira(fila *f) {
    if (f->inicio == NULL) {
        return NULL;
    }

    veiculo *removido = f->inicio;
    char *placa = (char *)malloc(9 * sizeof(char));
    strcpy(placa, removido->placa);

    f->inicio = removido->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(removido);
    return placa;
}

// funcoes estacionamento

void limpaPilhas(estacionamento *est) {
    for (int i = 0; i < NUM_PILHAS; i++) {
        while (est->P[i].topo != NULL) {
            char *placa = desempilha(&est->P[i]);
            free(placa);
        }
    }
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

        while (1) {
            scanf(" %c", &operacao);

            if (operacao == 'F') {
                printf("F\n\n");
                limpaPilhas(&est);
                break;
            } else if (operacao == 'E') {
                char placa[9];
                scanf("%s", placa);
                int indice = menorPilha(&est);
                if (empilha(&est.P[indice], placa)) {
                    printf("E %s\n", placa);
                } else {
                    printf("C %s\n", placa);
                }
            } else if (operacao == 'S') {
                char placa[9];
                scanf("%s", placa);
                int encontrado = 0;

                for (int i = 0; i < NUM_PILHAS; i++) {
                    fila auxiliar;
                    inicializaFila(&auxiliar);

                    while (est.P[i].topo != NULL) {
                        char *atual = desempilha(&est.P[i]);
                        if (strcmp(atual, placa) == 0) {
                            printf("S %s\n", atual);
                            encontrado = 1;
                            free(atual);
                            break;
                        } else {
                            enfileira(&auxiliar, atual);
                            free(atual);
                        }
                    }

                    while (auxiliar.inicio != NULL) {
                        char *atual = desenfileira(&auxiliar);
                        empilha(&est.P[i], atual);
                        free(atual);
                    }

                    if (encontrado) break;
                }

                if (!encontrado) {
                    printf("N %s\n", placa);
                }
            } else if (operacao == 'I') {
                int i;
                scanf("P%d", &i);
                imprimirPilha(&est.P[i], i);
            }
        }
    }
}

int main() {
    gerenciar_estacionamento();
    return 0;
}
