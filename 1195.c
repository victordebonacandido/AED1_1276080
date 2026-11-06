#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* esq;
    struct No* dir;
}No;

typedef struct No* arvore;

No* Inserir(arvore r, No* novo);
No* Criar_No(int valor);
void Liberar_arvore(arvore r);
void ERD(arvore r);
void RED(arvore r);
void EDR(arvore r);
void estilo(arvore r, int caso);


int main(){
    int num_casos = 0;
    scanf("%d", &num_casos);

    for(int i = 1; i <= num_casos; i++){
        int tam_arv = 0;
        scanf("%d", &tam_arv);
        arvore r = NULL;
        //MEXENDO COM A TREE
        for(int j = 0; j < tam_arv; j++){
            int no_temp;
            scanf("%d", &no_temp);
            No* novo = Criar_No(no_temp);
            r = Inserir(r, novo);
        }
        estilo(r, i);
        printf("\n");
        Liberar_arvore(r);
    }

    return 0;
}

No* Criar_No(int valor){
    No* novo = malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    else{
        novo->dir = NULL;
        novo->esq = NULL;
        novo->valor = valor;
        return novo;
    }
}

No* Inserir(arvore r, No* novo){
    if(r == NULL) return novo;
    else{
        No *guia = r, *guarda_pai;
        while(guia != NULL){
            guarda_pai = guia;
            if(guia->valor > novo->valor) guia = guia->esq;
            else guia = guia->dir;
        }
        if(guarda_pai->valor > novo->valor) guarda_pai->esq = novo;
        else guarda_pai->dir = novo;
        return r;
    }
}

void ERD(arvore r){
    if(r != NULL){
        ERD(r->esq);
        printf(" %d", r->valor);
        ERD(r->dir);
    }
}

void RED(arvore r){
    if(r != NULL){
        printf(" %d", r->valor);
        RED(r->esq);
        RED(r->dir);
    }
}

void EDR(arvore r){
    if(r != NULL){
        EDR(r->esq);
        EDR(r->dir);
        printf(" %d", r->valor);
    }
}

void Liberar_arvore(arvore r){
    if(r != NULL){
        Liberar_arvore(r->esq);
        Liberar_arvore(r->dir);
        free(r);
    }
}

void estilo(arvore r, int caso){
    printf("Case %d:\n", caso);

    printf("Pre.:");
    RED(r);
    printf("\n");

    printf("In..:");
    ERD(r);
    printf("\n");

    printf("Post:");
    EDR(r);
    printf("\n");
}
