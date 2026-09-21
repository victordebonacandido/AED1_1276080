/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1068
Data        : 21/09/2026
Objetivo    : Verificar se os parenteses de uma expressão matemática estão na ordem e quantidade correta
Uso da IA   : Eu consegui resolver o exercício, porém ficou dando erro no beecrownd, então usei o Gemini para
analisar os problemas, que era a falta de uma verificação, para resolver. Além disso, aproveitei e otimizei
com ajuda da IA o código, que é esse. O anterior tinham etapas desecessárias

-------------------------------------------------------------------------- */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct No{
    int valor;
    struct No *prox;
}No;


typedef struct pilha{
    No *topo;
}pilha;

//Coloca um novo valor no topo de uma pilha
void push(pilha *p, int v);

//retira o topo devolvendo o valor no topo
int pop(pilha *p);

//Verifica se uma pilha esta vazia retornando 1 se sim e 0 se falso
int esta_Vazia(pilha *p);

//Começa uma pilha;
void init(pilha *p);

//Libera todos os elementos de uma pilha, não incluso o p
void clear(pilha *p);


int main(){
    int tamanho = 1000;
    char* expressao = NULL;
    expressao = (char*)malloc((tamanho+1)*sizeof(char));

    //Continua lendo até a expressão for nula
    while(fgets(expressao, 1001, stdin) != NULL){
        pilha *p = (pilha*)malloc(sizeof(pilha));
        int i = 0;

        //Inicia a pilha
        init(p);
        //Coloca 1 se ( aparece e retira o 1 se  )  aparece
        while(expressao[i] != '\0'){
            if(expressao[i] == '(') {
                push(p, 1);
            }
            if(expressao[i] == ')') {
                if(p->topo == NULL) break;
                else{
                    pop(p);
                }
            }   
            i++;
        }
        //Se percorreu a string inteiro e o topo nulo, então está correto
        if(i == strlen(expressao) && p->topo == NULL) printf("correct\n");
        else printf("incorrect\n");
        //Garante que não sobre nada na pilha
        clear(p);
        //libera a pilha
        free(p);
    }
        free(expressao);
        return 0;
}


//Insere no topo
void push(pilha *p, int v){
    No* novo = (No*)malloc(sizeof(No));
    novo->prox = (p)->topo;
    novo->valor = v;
    (p)->topo = novo;
}

//Pop: Remove e retorna o topo
int pop(pilha *p){
    if(!(esta_Vazia(p))){
        int v_temp = (p)->topo->valor;
        No *temp = (p)->topo;
        (p)->topo = (p)->topo->prox;
        free(temp);
        return v_temp;
    }
    else{
        printf("Pilha vazia!\n");
        return 0;
    }
}

//estaVazia
int esta_Vazia(pilha *p){
    if((p)->topo == NULL) return 1;
    else return 0; 
}

//init: Inccia a pilha
void init(pilha *p){
    p->topo = NULL;
}

//Clear: Libera a pilha;
void clear(pilha *p){
    while((p)->topo != NULL){
        No *temp = (p)->topo;
        (p)->topo = (p)->topo->prox;
        free(temp);
    }
}



