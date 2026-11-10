#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char valor;
    struct No *esq;
    struct No* dir;
}No;

typedef struct No* arvore;

No* criar_no(int val);
void print_arvore(No* raiz);
arvore caminho_inversoo(int n, char* pre, char* in);
arvore liberar(arvore r);

int main(){
    int C = 0;
    scanf("%d", &C);
    for(int i = 0; i < C; i++){
        arvore r = NULL;
        int N = 0;
        scanf("%d", &N);
        char pre[N+1], in[N+1];
        scanf("%s %s", pre, in);   
        r = caminho_inversoo(N, pre, in);
        print_arvore(r);
        printf("\n");
        r = liberar(r);
    }

    return 0;
}

No* criar_no(int val){
    No* novo = malloc(sizeof(No));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->valor = val;
    return novo;
}


arvore caminho_inversoo(int n, char* pre, char* in){
    if(n <= 0) return NULL;
    No* raiz = criar_no(pre[0]);
    int pos = 0;

    while(in[pos] != pre[0]) pos++;

    raiz->esq = caminho_inversoo(pos, pre + 1, in);
    raiz->dir = caminho_inversoo(n - 1 - pos, pre + 1 + pos, in + pos+1);
    return raiz;
}

void print_arvore(No* raiz){
    if(raiz != NULL){
        print_arvore(raiz->esq);
        print_arvore(raiz->dir);
        printf("%c", raiz->valor);
    }
}

arvore liberar(arvore r){
    if(r != NULL){
        liberar(r->dir);
        liberar(r->esq);
        free(r);
    }
    return NULL;
}
