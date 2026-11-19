#include <stdio.h>
#include <stdlib.h>


int** GrafoM(int tam);
void LiberarGrafoM(int** matriz, int tam);
void DFS(int** grafo, int v, int tam, int *visitado);


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

        //Funcionamento do código

        printf("Case #%d:\n", i);
        int vezes = 0;
        int* visitado = calloc(num_vert, sizeof(int));
        for(int k = 0; k < num_vert; k++){
            if(!visitado[k]){
                DFS(M, k, num_vert, visitado);
                printf("\n");
                vezes++;
            }
        }
        printf("%d connected components\n\n", vezes);
        free(visitado);
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

void DFS(int** grafo, int v, int tam, int *visitado, int* conect){
    visitado[v] = 1;
    printf("%c,", v + 'a');
    for(int i = 0; i < tam; i++){
        if(grafo[v][i] == 1 && !visitado[i]){
            DFS(grafo, i, tam, visitado);
        }
    }
}

int* InserirOrdenadoVetor(int* vetor, int* tam, int valor) {
    vetor = realloc(vetor, (*tam + 1) * sizeof(int));
    int i = *tam - 1;
    while (i >= 0 && vetor[i] > valor) {
        vetor[i + 1] = vetor[i];
        i--;
    }
    vetor[i + 1] = valor;
    (*tam)++;
    return vetor;
}
