/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1110
Data        : 10/09/2026
Objetivo    : Roda a lógica de DiscardCards numa lista encadeada
Uso da IA   : Usei IA para  me guiar em algumas dúvidase fazer verificação de erros no meu código
-------------------------------------------------------------------------- */



#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* prox;
}No;

int Inserir(No** cabeca, int novovalor);

void remendar(No** cabeca);

int main(){
    No* cabeca = NULL;
    int num_cartas = 1;

    //Roda o código até o 0 ser digitado
    while(scanf("%d", &num_cartas) == 1 && num_cartas != 0){
        
        //Organiza o baralho
        for(int i = 1; i <= num_cartas; i++){
            Inserir(&cabeca,i);
        }

        printf("Discarded cards: ");
        //Roda a lógica do jogo até  apenas um nó sobrar
        while(cabeca -> prox != NULL){
            if((cabeca->prox)->prox == NULL) printf("%d", cabeca->valor);
            else printf("%d, ", cabeca -> valor);
            remendar(&cabeca);
            Inserir(&cabeca,(cabeca->valor));
            remendar(&cabeca);
        }

        printf("\n");
        printf("Remaining card: %d\n", cabeca -> valor);

        //Libera a cabeça para uma nova rodada
        free(cabeca);
        cabeca = NULL;
    }
    return 0;
}

//Insere numa lista um novonó com um novovalor de forma recursiva
int Inserir(No** cabeca, int novovalor){
    if(*cabeca == NULL){
        No *novoNo = (No*) malloc(sizeof(No));
        novoNo -> valor = novovalor;
        novoNo -> prox = NULL;
        *cabeca = novoNo;
        return 0;
    }
    else return Inserir(&((*cabeca) -> prox), novovalor);
}

//Recebe um nó e o remende n próximo nó, além disso exclui o nó "remendado"
void remendar(No** cabeca){
    if(*cabeca == NULL) return;
    No* temp = *cabeca; 
    *cabeca = (*cabeca)->prox;
    free(temp);
}