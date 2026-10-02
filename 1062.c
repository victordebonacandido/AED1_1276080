/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1062
Data        : 1/10/2026
Objetivo    : Saber se é possível alocar N números em ordem decrescente apenas podendo enfileirar ou empilhar e desempilhar
Dificuldade : Não cometer erros de memória
Uso de IA   : Me ajudou a identificar as regiões onde haviam erros nos códigos, apesar de que a maioria foi falta de atenção.
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int c;
    struct No *prox;
}No;

typedef struct pilha{
    No *topo;
}pilha;

//Funções para pilha!
void init_pilha(pilha *p);
int p_vazia(pilha *p);
int pop(pilha *p);
void push(pilha *p, int valor);
void clear(pilha *p);

//Funções para filas
void init_list(No** lista);
int lista_vazia(No** lista);
int inserir_fim(No** lista, int valor);
int pop_fila(No **lista);
void esvaziar(No **lista);

//Funções extras
void t_vetor_list(int *v, int tam, No** l);
int possivel(int* v, int tam);

int main(){
    int N = 1;
    while(1){
        scanf("%d", &N);
        if(N == 0) break;
        
        int* ordem = (int*)malloc(N*sizeof(int));
        
        //Fechamento do bloco
        while(1){
            scanf("%d", &ordem[0]);
            if(ordem[0] == 0){
                printf("\n");
                break;
            }

            for(int i = 1; i < N; i++){
                scanf("%d", &ordem[i]);
            }

            if(possivel(ordem, N))
                printf("Yes\n");

            else   
                printf("No\n");
        }
        free(ordem);
    }
    return 0;
}

//Função que verifica se é possível ou não organizar

int possivel(int* v, int tam){
    //Inicialização das listas
    No* cabeca;
    pilha *p = (pilha*)malloc(sizeof(pilha));
    init_list(&cabeca);
    init_pilha(p);

    t_vetor_list(v, tam, &cabeca);
    //Verificação
    int aux = tam;

    //Enquanto tiver mais de um elemento
    while(aux != 1){
    //Condições
        if(!lista_vazia(&cabeca) && cabeca->c == aux){
            pop_fila(&cabeca);
            aux--;
        }
        else if(!p_vazia(p) && p->topo->c == aux){
            pop(p);
            aux--;
        }
        else if(!lista_vazia(&cabeca)){
            push(p, pop_fila(&cabeca));
        }
        else{
            esvaziar(&cabeca);
            clear(p);
            return 0;
        } 
    }
    esvaziar(&cabeca);
    clear(p);
    return 1;   
}

//Função extra
void t_vetor_list(int *v, int tam, No** l){
    int i = tam-1;
    while(i >= 0){
        inserir_fim(l, v[i]);
        i--;
    }
}

//Funções pilha
void init_pilha(pilha *p){
    if(p != NULL){
        p->topo = NULL;
    }
}

int p_vazia(pilha *p){
    if(p->topo == NULL) return 1;
    else return 0;
}

int pop(pilha *p){
    if(!p_vazia(p)){
        int v_temp;
        No* temp = p->topo;
        v_temp = p->topo->c;
        p->topo = p->topo->prox;
        free(temp);
        return v_temp;
    }
    else{
        printf("A pilha está vazia!\n");
        return -1;
    }
}

void push(pilha *p, int valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->prox = p->topo;
    novo->c = valor;
    p->topo = novo;
}

void clear(pilha *p){
    while(p->topo != NULL){
        No* temp = p->topo;
        p->topo = p->topo->prox;
        free(temp);
    }
    free(p);
}

//Funções listas
void init_list(No** lista){
    *lista = NULL;
}

int lista_vazia(No** lista){
    if((*lista) == NULL) return 1;
    else return 0;
}

int inserir_fim(No** lista, int valor){
    if((*lista) == NULL){
        No *novo = (No*)malloc(sizeof(No));
        (*lista) = novo;
        novo->prox = NULL;
        novo->c = valor;
        return 0;
    }
    else return inserir_fim(&((*lista)->prox), valor);
}

int pop_fila(No **lista){
    if((*lista) != NULL){
        int v_temp = (*lista)->c;
        No* temp = *lista;
        *lista = (*lista)->prox;
        free(temp);
        return v_temp;
    }
    else{
        printf("Lista vazia!\n");
        return -1;
    }
}

void esvaziar(No **lista){
    while((*lista) != NULL){
        No *temp = (*lista);
        (*lista) = (*lista)->prox;
        free(temp);
    }
    free(*lista);
}
