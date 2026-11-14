#include <stdio.h>
#include <stdlib.h>

// 1. Nó da Árvore
typedef struct Folha {
    int valor;
    struct Folha *esq;
    struct Folha *dir;
} Folha;

typedef struct Folha *Arvore;

// 2. Nó da Fila (Tag 'No' idêntica ao alias 'No')
typedef struct No {
    Folha *folha;
    struct No *prox;
} No;

// 3. Fila
typedef struct Fila {
    No *inicio;
    No *fim;
} Fila;


void Funcionamento(Arvore r, Fila* f);
No* CriarNo(Folha* valor);
Folha* CriarFolha(int valor);
void InitFila(Fila* f);
void Inserir_Fila(Fila* f, Folha* valor);
void LiberarFila(Fila* f);
Arvore InserirArvore(Arvore r, Folha* novo);
void LiberarArvore(Arvore r);
void ImprimirFila(Fila* f);
void PopFila(Fila* f);



int main(){
    int N = 0;
    scanf("%d", &N);
    //Quantas instâncias rodarão
    for(int i = 1; i <= N; i++){
        Arvore r = NULL;
        //Tamanho da árvore
        int tam = 0;
        scanf(" %d", &tam);
        for(int j = 0; j < tam; j++){
            int item = 0;
            scanf(" %d", &item);
            r = InserirArvore(r, CriarFolha(item));
        }
        Fila* f = malloc(sizeof(Fila));
        InitFila(f);
        //Término de processar a fila, agora printar a fila e liberar memória
        printf("Case %d:\n", i);
        Funcionamento(r,f);
        LiberarFila(f);
        LiberarArvore(r);
    }

    return 0;
}

No* CriarNo(Folha* valor){
    No* novo = malloc(sizeof(No));
    novo->prox = NULL;
    novo->folha = valor;
    return novo;
}

Folha* CriarFolha(int valor){
    Folha* novo = malloc(sizeof(Folha));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->valor = valor;
    return novo;
}

void InitFila(Fila* f){
   f->inicio = NULL;
   f->fim = NULL;
}

void Inserir_Fila(Fila* f, Folha *valor){
    if(f->inicio == NULL){
        f->fim = CriarNo(valor);
        f->inicio = f->fim;
    }
    else{
        f->fim->prox = CriarNo(valor);
        f->fim = f->fim->prox;
    }
}

void LiberarFila(Fila* f){
    while(f->inicio != NULL){
        No* temp = f->inicio;
        f->inicio = f->inicio->prox;
        free(temp);
    }
}

void ImprimirFila(Fila* f){
    No* temp = f->inicio;
    while(temp != NULL){
        printf("%d ", temp->folha->valor);
        temp = temp->prox;
    }
    printf("\n");
}

void PopFila(Fila* f){
    No* temp = f->inicio;
    f->inicio = f->inicio->prox;
    free(temp);
}

Arvore InserirArvore(Arvore r, Folha* novo){
    if(r == NULL) r = novo;
    else{
        Folha* guia, *pai = r;
        guia = pai; 
        while(guia != NULL){
            pai = guia;
            if(guia->valor > novo->valor) guia = guia->esq;
            else guia = guia->dir;
        }
        if(pai->valor > novo->valor) pai->esq = novo;
        else pai->dir =  novo;
    }
    return r;
}

void LiberarArvore(Arvore r){
    if(r != NULL){
        LiberarArvore(r->dir);
        LiberarArvore(r->esq);
        free(r);
    }
}

void Funcionamento(Arvore r, Fila* f){
    if (r == NULL) return;
    Inserir_Fila(f, r);
    while(f->inicio != NULL){
        if (f->inicio->folha != r) printf(" ");
        printf("%d", f->inicio->folha->valor);

        if(f->inicio->folha->esq != NULL){
            Inserir_Fila(f, f->inicio->folha->esq);
        }
        
        if(f->inicio->folha->dir != NULL){
            Inserir_Fila(f, f->inicio->folha->dir);
        }

        PopFila(f); 
    }
    printf("\n\n");
}
