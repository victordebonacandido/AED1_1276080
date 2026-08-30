#include <stdio.h>
#include <stdlib.h>
//Lembre-se dos dois free

int verificar(int **M, int inst);

int verifica_vetor(int vetor[], int tam);


int main(){
    int inst = 0;
    scanf("%d", &inst);

    //Alocação dinâmica da matriz
    int linhas = inst*9, colunas = 9;
    int **M = malloc(linhas*sizeof(int*));
   
    for(int i = 0; i < linhas; i++){
        M[i] = malloc(colunas*(sizeof(int)));
    }

    //Leu e guardou todos os elementos.
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf("%d", &M[i][j]);
        }  
    }

    for(int i = 1; i <= inst; i++){
        printf("Instancia %d\n", i);

        if(verificar(M, i)){
            printf("SIM\n\n");
        }
        else{
            printf("NAO\n\n");
        }
    }

    for(int i = 0; i < linhas; i ++){
        free(M[i]);
    }
    free(M);

    return 0;
}

int verificar(int **M, int inst){

    //Verifica as linhas
    for(int i = 0 + (inst-1)*9; i < 9 + (inst-1)*9; i++){
        for(int j = 8; j >= 0; j--){
            for(int k = 0; k < j; k++){
                if(M[i][j] == M[i][k]) return 0;
            }
        }
    }

    //Verifica as colunas
    for(int j = 0; j < 9; j++){
        for(int i = 8 + (inst-1)*9; i >= 0 + (inst-1)*9; i--){
            for(int k = 0 + (inst-1)*9; k < i; k++){
                if(M[i][j] == M[k][j]) return 0;
            }
        }
    }

    //Verifica a 3x3
    //Selecionei o bloco
    for(int blocoi = 0; blocoi < 3; blocoi++){
        for(int blocoj = 0; blocoj < 3; blocoj++){
            //Selecionei a linha e coluna dentro do bloco.

            int vetor[9] = {0};
            int contagem = 0;
            for(int i = (3*blocoi + (inst-1)*9); i < (3*blocoi + 3 + (inst-1)*9); i++){
                for(int j = 3*blocoj; j < 3*blocoj + 3; j++){
                    vetor[contagem] = M[i][j];
                    contagem++;
                }
            }
            if(!(verifica_vetor(vetor,9))) return 0;
        }
    }

    return 1;
}


int verifica_vetor(int vetor[], int tam){
    for(int i = tam-1 ; i >= 0; i --){
        for(int j = 0; j < i; j ++){
            if(vetor[i] == vetor[j]) return 0;
        }
    }
    return 1;
}