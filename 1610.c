/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1610
Data        : 30/08/2026
Objetivo    : Ver se há um ciclo em um grafo direcioando
Dificuldade : Aprender a usar o grafo em vez de matriz como uma lista
Uso de IA   : Usei pq não parava de dar runtime error e, no final, era a falta de um &
-------------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* prox;
}No;

typedef struct GrafoNo{
    int numVertices;
    No **listaVertices;
}Grafo;

No* CriarNo(int valor);
void LiberarLista(No* lista);
void PushLista(No** lista,int valor);
int HaCiclo(Grafo *g, int v, int visitado[]);
Grafo* CriarGrafo(int numverticies);
void LiberarGrafo(Grafo* g);


int main(){
    int instancias = 0;
    scanf(" %d", &instancias);
    for(int i = 0; i < instancias; i++){
        int num_doc, num_vert;
        scanf(" %d %d", &num_doc, &num_vert);
        Grafo *g = CriarGrafo(num_doc);
        for(int j = 0; j < num_vert; j++){
            int QualNo, Info;
            scanf(" %d", &QualNo);
            scanf("%d", &Info);
            PushLista(&(g->listaVertices[QualNo-1]), Info);
        }
        int visitado[num_doc];
        int tem_ciclo = 0;
        for(int k = 0; k < num_doc; k++){
            visitado[k] = 0;
        }
        
        for(int l = 0; l < num_doc; l++){
            if(visitado[l] == 0){
                if(HaCiclo(g, l, visitado)){
                    tem_ciclo = 1;
                    break;
                }
            }
        }

        if(tem_ciclo) printf("SIM\n");
        else printf("NAO\n");
        
        LiberarGrafo(g);
    }
}

No* CriarNo(int valor){
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

void LiberarLista(No* lista){
   No* temp ;
   while(lista != NULL){
        temp = lista;
        lista = lista->prox;
        free(temp);
   }
}

void PushLista(No** lista,int valor){
    No* novo = CriarNo(valor);
    novo->prox = (*lista);
    (*lista) = novo;
}

int HaCiclo(Grafo *g, int v, int visitado[]){
    if(visitado[v] == 1) return 1;
    if(visitado[v] == 2) return 0;
    visitado[v] = 1;
    No* temp = g->listaVertices[v];
    while(temp != NULL){
        if(HaCiclo(g, (temp->valor)-1, visitado)) return 1;
        temp = temp->prox;
    }
    visitado[v] = 2;
    return 0;
}

Grafo* CriarGrafo(int numverticies){
    Grafo* g = malloc(sizeof(Grafo));
    g->numVertices = numverticies;
    g->listaVertices = calloc(g->numVertices, sizeof(No*));
    return g;
}

void LiberarGrafo(Grafo* g){
    for(int i = 0; i < g->numVertices; i++){
        LiberarLista(g->listaVertices[i]);
    }
    free(g->listaVertices);
    free(g);
}
