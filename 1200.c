#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char letra;
    struct No* esq;
    struct No* dir;
}No;

typedef struct No* arvore;

No* Criar_No(char c);
arvore Inserir(arvore r, No* novo);
int Busca_arvore(arvore r, char c);
void INFIX(arvore r);
void PREFIX(arvore r);
void POSFIX(arvore r);


int main(){
    arvore r = NULL;
    while(EOF){
        char* v = malloc(10*sizeof(char));
        scanf("%s", v);
        //Ou é P ou é I
        if(v[1] == '\0'){
            char letra;
            scanf("%c", &letra);
            if(v[0] == 'I'){
                r = Inserir(r, Criar_No(letra));
            }
            else{
                if(Busca_arvore(r, letra)){
                    printf("%c existe\n", letra);
                }
                else printf("%c não existe\n", letra);
            }
        }

        else{
            if(!strcmp(v, "INFIXA")) INFIX(r);
            if(!strcmp(v, "POSFIXA")) POSFIX(r);
            if(!strcmp(v, "PREFIXA")) PREFIX(r);
            printf("\n");
        }
        free(v);
    }
    return 0;
}

No* Criar_No(char c){
    No* novo =  malloc(sizeof(No));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->letra = c;
    return novo;
}

arvore Inserir(arvore r, No* novo){
    if(r == NULL) return novo;
    else{
        No *pai, *guia;
        pai = r;
        guia = pai;
        while(guia != NULL){
            pai = guia;
            if(guia->letra > novo->letra) guia = guia->esq;
            else guia = guia->dir;
        }
        if(pai->letra > novo->letra) pai->esq = novo;
        else pai->dir = novo;
        return r;
    } 
}

int Busca_arvore(arvore r, char c){
    if(r == NULL) return 0;
    if(r->letra == c) return 1;
    else{
        Busca_arvore(r->dir, c);
        Busca_arvore(r->esq, c);
    }
}

void INFIX(arvore r){
    if(r != NULL){
        INFIX(r->esq);
        printf("%c", r->letra);
        INFIX(r->dir);
    }
}

void PREFIX(arvore r){
    if(r != NULL){
        printf("%c", r->letra);
        PREFIX(r->esq);
        PREFIX(r->dir);
    }
}

void POSFIX(arvore r){
    if(r != NULL){
        POSFIX(r->esq);
        POSFIX(r->dir);
        printf("%c", r->letra);
    }
}
