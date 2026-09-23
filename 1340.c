/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1340
Data        : 22/09/2026
Objetivo    : Recebe N operações, sendo a operação 1 uma inserção numa lista e a operações 2 a retirada de um elemento da lista
cada operação é seguida do elemento retirada. A saída deve retorna o tipo da lista(pilha, fila, fila preferencial) ou não tem
certeza ou impossível
Uso da IA   : Usei a IA para me guiar num problema específico de Memory Leak, era um endereço de acesso mal colocado na pilha,
mas eu apenas pedi para apontar a região. Além disso, a primeira resolução ultrapassava o tempo por conta da função organizar_lista
ser recursurva, fiz uma função que fazia a inserção já organizando, mas que falhava em certos casos, pedi para a IA arrumar e refiz
a função
-------------------------------------------------------------------------- */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int valor;
    struct No *prox;
}No;

typedef struct Pilha{
    No *topo;
}pilha;

//Funções para PILHA

//Recebe uma pilha e a inicia, ou seja, deixando-a vazia
void init_pilha(pilha *p);

//Verifica se a pilha está vazia, se sim retorna 1, senão 0
int p_vazia(pilha *p);

//Recebe uma pilha, retira o topo e retorna seu valor
int pop(pilha *p);

//Recebe uma pilha e um valor inteiro, coloca o valor inteiro no topo da pilha
void push(pilha *p, int valor);

//Libere a memória de uma pilha
void clear(pilha *p);

//Funções para filas

//Recebe uma lista e garante que ela é vazia
void init_list(No** lista);

//Verifica se a lista está vazia, retornando 1 se sim, senão, 0
int lista_vazia(No** lista);

//Recebe uma lista e um valor inteiro, inserindo o valor ao final da lista
int inserir_fim(No** lista, int valor);

//Recebe uma lista e um valor inteiro, insere o valor em ordem decrescente da lista
void inserir_pref(No** lista, int valor);

//Remove o último valor da lista e retorna o valor
int pop_fila(No **lista);

//Recebe uma lista e um valor inteiro. Troca os elementos vizinhos em ordem decrescente, retornando troca+1 se houve alguma troca
int organizar_lista(No** lista, int troca);

//Recebe uma lista e libera todos os seus nós
void esvaziar(No **lista);

int main(){
    int N = 0;
    //Roda até o fim do arquivo
    while(scanf("%d",&N) != EOF){

        //Variáveis de verificação
        int npilha = 0, nfila = 0, nfilapref = 0, num_dois = 0;
        No *fila = NULL, *fila_pref = NULL;

        //Declaração das listas
        pilha *p  = (pilha*)malloc(sizeof(pilha));
        init_pilha(p);

        //Lê a operação e o número
        int op, val;

        //Roda o número de operações digitadas em N
        for(int i = 0; i < N; i++){
            scanf("%d %d", &op, &val);

            //Inserção dos elementos
            if(op == 1){
                inserir_fim(&fila,val);
                inserir_pref(&fila_pref,val);
                push(p, val);
                
            }
            //Retirada dos elementos
            else{
                num_dois++;
                if(pop(p) == val) npilha++;
                if(pop_fila(&fila) == val) nfila++;
                if(pop_fila(&fila_pref) ==  val) nfilapref++;
            }
        }
        
        //Verificação do tipo de estrutura
        if((npilha == num_dois && nfila == num_dois)||(npilha == num_dois && nfilapref == num_dois)||(nfila == num_dois && nfilapref == num_dois)) printf("not sure\n");
        else if(npilha == num_dois) printf("stack\n");
        else if(nfila == num_dois) printf("queue\n");
        else if(nfilapref == num_dois) printf("priority queue\n");
        else printf("impossible\n");

        //Limpar a memória das filas e pilhas
        if(p->topo != NULL){
            clear(p);
            esvaziar(&fila);
            esvaziar(&fila_pref);
        } 
        free(fila);
        free(p);
        free(fila_pref);
        
    }
}

//Função para lista preferencial
int organizar_lista(No** lista, int troca) {
    if( *lista == NULL || (*lista)->prox == NULL) return troca;
    if((*lista)->valor > (*lista)->prox->valor) return organizar_lista(&((*lista)->prox), troca);
    else{
        int temp = (*lista) ->valor;
        (*lista) ->valor = (*lista)->prox->valor;
        (*lista)->prox->valor = temp;
        return organizar_lista(&((*lista)->prox), troca+1);
    }
}


//Funções para lista
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
        novo->valor = valor;
        return 0;
    }
    else return inserir_fim(&((*lista)->prox), valor);
}

void inserir_pref(No** lista, int valor){
    if((*lista) == NULL|| (*lista)->valor < valor){
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->prox = (*lista);
        (*lista) = novo;
    }
    else return inserir_pref(&((*lista)->prox),valor);
}

int pop_fila(No **lista){
    if((*lista) != NULL){
        int v_temp = (*lista)->valor;
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
    if((lista_vazia(lista))) return;
    while((*lista)->prox != NULL){
        No *temp = (*lista);
        (*lista) = (*lista)->prox;
        free(temp);
    }
}

//Funções para pilha!
void init_pilha(pilha *p){
    if(p != NULL){
        p->topo = NULL;
    }
}

int p_vazia(pilha *p){
    if(p->topo == NULL) return 0;
    else return 1;
}

int pop(pilha *p){
    if(p_vazia(p)){
        int v_temp = 0;
        No* temp = p->topo;
        v_temp = p->topo->valor;
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
    novo->valor = valor;
    p->topo = novo;
}

void clear(pilha *p){
    while(p->topo != NULL){
        No* temp = p->topo;
        p->topo = p->topo->prox;
        free(temp);
    }
}

