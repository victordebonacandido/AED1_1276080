/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1077
Data        : 28/09/2026
Objetivo    : Recebe um número N que indica a quantidade de operações, depois recebe uma expressão de formato infixa
e a transforma para posfixa o imprimindo.
Uso da IA   : Fiquei uns 5 dias tentando implementar minha solução a partir  de diversas listas encadeadas, mas
parecia difícil e compliado demais. Usei a IA para ver se o caminho vazia sentido e se tinha outra forma mais 
simples de se resolver, ela não escreveu nenhum código, apenas me explicou a lógica do algoritimo.
-------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char c;
    struct No *prox;
}No;

typedef struct pilha{
    No *topo;
}pilha;

//Funções para pilha!
void init_pilha(pilha *p);
int p_vazia(pilha *p);
char pop(pilha *p);
void push(pilha *p, char valor);
void clear(pilha *p);

//Funções para filas
void init_list(No** lista);
int lista_vazia(No** lista);
int inserir_fim(No** lista, char valor);
char pop_fila(No **lista);
void esvaziar(No **lista);

//Funções extras
void posfix(char* expressao);
void t_list_str(No **lista,char* expressao);
int operador(char c);
int qual_operador(char c);
void print_str(char* expressao);

int main(){
    int N = 0;
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        char *expressao = (char*)malloc(300*sizeof(char));
        scanf("%s", expressao);
        posfix(expressao);
        print_str(expressao);
        //Garante que não haja erro de memória
        free(expressao);

    }
    return 0;
}

//printar string
void print_str(char* expressao){
    int i = 0;
    while(expressao[i] != '\0'){
        printf("%c", expressao[i]);
        i++;
    }
    printf("\n");
}


//Organiza para posfix; sem para por enquanto
void posfix(char* expressao){
    //Declaração de variáveis
    pilha *p = (pilha*)malloc(sizeof(pilha));
    No *fila;
    init_list(&fila);
    init_pilha(p);
    int tamanho = strlen(expressao);


    for(int i = 0; i < tamanho; i++){
        if(operador(expressao[i])){
            if(expressao[i] == '(') push(p, expressao[i]);
            else if(expressao[i] == ')'){
                while(!p_vazia(p) && p->topo->c != '('){
                    inserir_fim(&fila, pop(p));
                }
                if(!p_vazia(p)) pop(p);//Tirar o (
            }
            else{
                while(p->topo != NULL && qual_operador(p->topo->c) >= qual_operador(expressao[i])){
                    inserir_fim(&fila, pop(p));  
                }
                push(p, expressao[i]);
            }
        }
        else inserir_fim(&fila, expressao[i]);
       
    }
    //Se a minha pilha ainda não estiver vazia, coloca o resto dos operadores na lista
    while(!p_vazia(p)){
        if(p->topo->c != '(') inserir_fim(&fila, pop(p));
        else pop(p);
    } 
    
    t_list_str(&fila, expressao);

    clear(p);
    esvaziar(&fila);
}


//Função que transforma lista em string
void t_list_str(No **lista,char* expressao){
    int tam = 0;
    while(!lista_vazia(lista)){
        expressao[tam] = pop_fila(lista);
        tam++;
    }
    expressao[tam] = '\0';
}

//Função que verifica se é um operador ou não, retornando o operador se for;
int operador(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')') return 1;
    else return 0;
}

int qual_operador(char c){
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if ( c == '^') return 3;
    if(c == ')') return 14;
    if(c == '(') return 0;
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

char pop(pilha *p){
    if(!p_vazia(p)){
        char v_temp;
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

void push(pilha *p, char valor){
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

int inserir_fim(No** lista, char valor){
    if((*lista) == NULL){
        No *novo = (No*)malloc(sizeof(No));
        (*lista) = novo;
        novo->prox = NULL;
        novo->c = valor;
        return 0;
    }
    else return inserir_fim(&((*lista)->prox), valor);
}

char pop_fila(No **lista){
    if((*lista) != NULL){
        char v_temp = (*lista)->c;
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
    if((lista_vazia(lista))){
        free(*lista);
        return;
    } 
    while((*lista)->prox != NULL){
        No *temp = (*lista);
        (*lista) = (*lista)->prox;
        free(temp);
    }
}
