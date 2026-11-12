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
void INFIX(arvore r, int *primeiro);
void PREFIX(arvore r, int *primeiro);
void POSFIX(arvore r, int *primeiro);
int compara_string(char* s1, char* s2);
void liberar(arvore r);


int main(){
    arvore r = NULL;
    char v[10];
    while(scanf("%s", v) != EOF){
        //Ou é P ou é I
        if(strlen(v) < 2){
            char letra;
            scanf(" %c", &letra);
            if(v[0] == 'I'){
                r = Inserir(r, Criar_No(letra));
            }
            else if(v[0] == 'P')
            {
                if(Busca_arvore(r, letra)){
                    printf("%c existe\n", letra);
                }
                else printf("%c nao existe\n", letra);
            }
        }

        else{
            int primeiro = 1;
            char infix[7] = "INFIXA";
            char posfix[8] = "POSFIXA";
            char prefix[8] = "PREFIXA";
            if(compara_string(v, infix)) INFIX(r, &primeiro);
            if(compara_string(v, posfix)) POSFIX(r, &primeiro);
            if(compara_string(v, prefix)) PREFIX(r, &primeiro);
            printf("\n");
        }
    }
    liberar(r);
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
        if(r->letra > c) return Busca_arvore(r->esq, c);
        else return Busca_arvore(r->dir, c);
    }
}

void INFIX(arvore r, int *primeiro){
    if(r != NULL){
        INFIX(r->esq, primeiro);
        if(*primeiro){
            printf("%c", r->letra);
            *primeiro = 0;
        }
        else printf(" %c", r->letra);
        INFIX(r->dir, primeiro);
    }
}

void PREFIX(arvore r, int *primeiro){
    if(r != NULL){
        if(*primeiro){
            printf("%c", r->letra);
            *primeiro = 0;
        }
        else printf(" %c", r->letra);
        PREFIX(r->esq, primeiro);
        PREFIX(r->dir, primeiro);
    }
}

void POSFIX(arvore r, int *primeiro){
    if(r != NULL){
        POSFIX(r->esq, primeiro);
        POSFIX(r->dir, primeiro);
        if(*primeiro){
            printf("%c", r->letra);
            *primeiro = 0;
        }
        else printf(" %c", r->letra);
    }
}

int compara_string(char* s1, char* s2){
    if(strlen(s1) != strlen(s2)) return 0;
    else{
        int i = 0;
        while(i <= strlen(s1)){
            if(s1[i] != s2[i]) return 0;
            i++;
        }
    return 1;
    }
}

void liberar(arvore r){
    if(r != NULL){
        liberar(r->esq);
        liberar(r->dir);
        free(r);
    }
}
