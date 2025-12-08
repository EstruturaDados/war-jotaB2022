#include <stdio.h>
#include <string.h>

//Definição de TAMANHOS'''

#define TAM_NOME  31
#define TAM_COLOR  11
#define TAM_TERRI  5

//Criação da Struct'''
struct Terri{
    char nome[TAM_NOME];
    char color[TAM_COLOR];
    int tropas;

};

//Método Principal'''
int main(){

// Chamando o struct e passando para variavel Terri'''
    struct Terri Territorio[TAM_TERRI];
    
    // Laços em For e Cadastro dos Campos do Territorio'''
    for(int k = 0; k < TAM_TERRI; k++){
        printf("Cadastre o Nome do Terrritorio %d ", k+1);
        scanf("%30s", Territorio[k].nome);
       

        printf("Cadastre a Cor do Terrritorio %d ", k+1);
        scanf("%10s", Territorio[k].color);

        printf("Cadastre o Número de Tropas do Terrritorio %d ", k+1);
        scanf("%d", &Territorio[k].tropas);
    }

   // Exibição'''
    for(int i =0; i < TAM_TERRI; i++){

        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", Territorio[i].nome);
        printf("Cor: %s\n", Territorio[i].color);
        printf("Tropas: %d\n\n", Territorio[i].tropas);
    }
    return 0;
}




