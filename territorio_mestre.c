#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_NOME 30
#define TAM_COR 10
#define MISSION_TOTAL 5
#define MISSON_TAM 100

// ===== Struct Territorio =====
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Prototipo das funções...
void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirTerritorios(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void validationMode(Territorio *mapa, int atacante, int defensor, int qtd);
void validationAlocationMemory(Territorio *mapa);
void liberarMemoria(Territorio *mapa);
void atribuirMissao(char* destino, char missoes[][MISSON_TAM], int totalMissoes);
void exibirMissao(char* missao);
int verificarMissao(char *missao, Territorio *mapa, int qtd); 

// ===== Função principal =====
int main() {
    int opcoes;
    int atacante, defensor;
    int qtd = 0;
    
    Territorio *mapa = NULL;
    char missao_usuario[MISSON_TAM];  

    char vector_missao[MISSION_TOTAL][MISSON_TAM] = {
    "Conquistar 3 territorios", 
    "Eliminar todas as tropas da cor vermelha", 
    "Conquistar metade do mapa", 
    "Eliminar um territorio inimigo", 
    "Vencer 3 ataques consecutivos"
};
  
    srand(time(NULL));
    opcoes = 0;

 // Atribuindo uma missão ao usuário
    atribuirMissao(missao_usuario, vector_missao, MISSION_TOTAL);
    exibirMissao(missao_usuario);

    while (opcoes != 4){
        printf("\n[===MENU===]\n");
        printf("1 -- Cadastro de Territorios\n");
        printf("2 -- Exibir Territorios\n");
        printf("3 -- Modo Ataque\n");
        printf("4 - Sair do Jogo \n");
        printf("Digite uma opção:");
        scanf("%d", &opcoes);
        
        switch (opcoes) {
        case 1:
            printf("Quantos territorios deseja cadastrar? ");
            scanf("%d", &qtd);
            mapa = (Territorio *)calloc(qtd, sizeof(Territorio));
            validationAlocationMemory(mapa);
            cadastrarTerritorios(mapa, qtd);
            break;
        case 2:
            exibirTerritorios(mapa, qtd);
            break;
        case 3:
            printf("\nEscolha o territorio ATACANTE (indice): ");
            scanf("%d", &atacante);

            printf("Escolha o territorio DEFENSOR (indice): ");
            scanf("%d", &defensor);
            validationMode(mapa, atacante, defensor, qtd);

            if (verificarMissao(missao_usuario, mapa, qtd)) {
                printf("\nMissão Concluída com Sucesso!\n");
            }
            break;
        case 4:
            printf("Saindo do jogo...\n");
            break;
        }
    }
    
    // Liberação de memória alocada
    liberarMemoria(mapa);
    return 0;
}

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
// ===== Função para Atacar =====
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque!\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");

        int tropasTransferidas = defensor->tropas - 1;
        if (tropasTransferidas < 1) tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;
    } else {
        printf("Defensor resistiu! Atacante perde 1 tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}
// ===== Função para modo de Atacar se é da mesma cor =====
void validationMode(Territorio *mapa, int atacante, int defensor, int qtd){
    if (atacante < 0 || atacante >= qtd || defensor < 0 || defensor >= qtd) {
        printf("Indice invalido!\n");
    } else if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("Nao e possivel atacar um territorio da mesma cor!\n");
    } else {
        atacar(&mapa[atacante], &mapa[defensor]);
        exibirTerritorios(mapa, qtd);
    }
}
// verificação da alocação de memoria
void validationAlocationMemory(Territorio *mapa) {
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria!\n");
    }
}
//liberar Memoria( Evitar vazamento de memoria)
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// Função para atribuir missão ao jogador
void atribuirMissao(char* destino, char missoes[][MISSON_TAM], int totalMissao) {
    int sorte_missao = rand() % totalMissao;
    strcpy(destino, missoes[sorte_missao]);
}

// Função para exibir missão do jogador
void exibirMissao(char* missao) {
    printf("\n--- SUA MISSAO --- \n");
    printf("%s \n", missao);
}

// Função para verificar se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int qtd) {
    // Implementação das verificações das missões (retorno de 1 ou 0)
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int contador = 0;
        for (int i = 0; i < qtd; i++) {
            if (mapa[i].tropas > 0) contador++;
        }
        return contador >= 3;
    }

    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;  // Missão não cumprida
            }
        }
        return 1;  // Missão cumprida
    }

    // Outras missões podem ser verificadas aqui...

    return 0;  // Caso a missão não tenha sido reconhecida
}