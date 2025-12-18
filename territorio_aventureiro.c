#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10

// ===== Struct Territorio =====
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// ===== Função para cadastrar territórios =====
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// ===== Função para exibir territórios =====
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ===== Função de ataque =====
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque!\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");

        int tropasTransferidas = defensor->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf("Defensor resistiu! Atacante perde 1 tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

// ===== Função para liberar memória =====
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// ===== Função principal =====
int main() {
    int qtd;
    int atacante, defensor;

    srand(time(NULL));

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica
    Territorio *mapa = (Territorio *)calloc(qtd, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    printf("\nEscolha o territorio ATACANTE (indice): ");
    scanf("%d", &atacante);

    printf("Escolha o territorio DEFENSOR (indice): ");
    scanf("%d", &defensor);

    // Validações
    if (atacante < 0 || atacante >= qtd || defensor < 0 || defensor >= qtd) {
        printf("Indice invalido!\n");
    }
    else if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("Nao e possivel atacar um territorio da mesma cor!\n");
    }
    else {
        atacar(&mapa[atacante], &mapa[defensor]);
        exibirTerritorios(mapa, qtd);
    }

    liberarMemoria(mapa);
    return 0;
}



