#include <stdio.h>
#include <stdlib.h>

int main(){

}

int** matriz(int tam){
    int** M = malloc(tam*sizeof(int*));
    
    for(int i = 0; i < tam; i++){
        M[i] = malloc(tam*sizeof(int));
    }

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            M[i][j] = 0;
        }
    }

    return M;
}

void LiberarMatriz(int** matriz, int tam){
    for(int i = 0; i < tam; i++){
        free(matriz[i]);
    }
    free(matriz);
}
