#include <stdio.h>
#include <stdlib.h>

int** GrafoM(int tam);
void LiberarGrafoM(int** matriz, int tam);
void DFS(int** grafo, int v, int tam, int *visitado, int* conect, int* pos);
void BubbleSort(int* vetor, int fim);
int EncontrarFim(int* vetor);
void PrintarVetor(int* vetor, int fim);

int main(){
    int instancias;
    scanf("%d", &instancias);
    for(int i = 1; i <= instancias; i++){
        int num_vert, num_arestas;
        scanf(" %d %d", &num_vert, &num_arestas);

        int** M = GrafoM(num_vert);

        for(int j = 0; j < num_arestas; j++){
            char no1, no2;
            scanf(" %c %c", &no1, &no2);
            M[no1-'a'][no2-'a'] = 1;
            M[no2-'a'][no1-'a'] = 1;
        }

        printf("Case #%d:\n", i);
        int vezes = 0;
        int* visitado = calloc(num_vert, sizeof(int));
        int* controle = malloc(27*sizeof(int));

        for(int k = 0; k < num_vert; k++){
            if(!visitado[k]){
                for(int j = 0; j < 27; j++){
                    controle[j] = -1;
                }
                int pos = 0;
                DFS(M, k, num_vert, visitado, controle, &pos);
                int fim = EncontrarFim(controle);
                BubbleSort(controle, fim);
                PrintarVetor(controle, fim);
                vezes++;
            }
        }

        printf("%d connected components\n\n", vezes);
        free(visitado);
        free(controle);
        LiberarGrafoM(M, num_vert);
    }
    return 0;
}

int** GrafoM(int tam){
    int** Matriz = calloc(tam, sizeof(int*));
    for(int i = 0; i < tam; i++){
        Matriz[i] = calloc(tam, sizeof(int));
    }
    return Matriz;
}

void LiberarGrafoM(int** matriz, int tam){
    for(int i = 0; i < tam; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void DFS(int** grafo, int v, int tam, int *visitado, int* conect, int* pos){
    visitado[v] = 1;
    conect[(*pos)++] = v;
    for(int i = 0; i < tam; i++){
        if(grafo[v][i] == 1 && !visitado[i]){
            DFS(grafo, i, tam, visitado, conect, pos);
        }
    }
}

void BubbleSort(int* vetor, int fim){
    for(int i = 0; i < fim-1; i++){
        for(int j = i+1; j < fim; j++){
            if(vetor[i] > vetor[j]){
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}

int EncontrarFim(int* vetor){
    int i = 0;
    while(vetor[i] != -1){
        i++;
    }
    return i;
}

void PrintarVetor(int* vetor, int fim){
    for(int i = 0; i < fim; i++){
        printf("%c,", vetor[i] + 'a');
    }
    printf("\n");
}
