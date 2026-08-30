
/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 20/08/2026
Objetivo    : Verificar N instâncias de Sudokus e devolver se a resolução é certa ou errada
Dificuldade : Tentei fazer por recursão a verificação do sudoku, mas falhei e me rendi
ao método iterativo.
Uso de IA   : Usei para fazer a verificação do código, pois como a entrada é
grande demais para se repetir, fiz a IA testâ-la. Além disso, usei para verificar
se a lógica do código estava correta.
-------------------------------------------------------------------------- */

#include <stdio.h>


int verificar_sudoku(int M[][9], int instancia);


int main(){
    //Descobre quantas intâncias irá checar
    int num_matriz = 0;
    printf("Número de instâncias?\n");
    scanf("%d", &num_matriz);

    //Escaneia os elementos das matrizes
    int M[9*num_matriz][9];
    for(int i = 0; i < 9*num_matriz; i++){
        for(int j = 0; j < 9; j++){
            scanf("%d", &M[i][j]);
        }
    }

    //Verifica as instâncias e imprime o resultado
    for(int vezes = 1; vezes <= num_matriz; vezes++){
        if(verificar_sudoku(M,vezes)){
            printf("Instância %d\n", vezes);
            printf("SIM");
        }
        else{
            printf("Instância %d\n", vezes);
            printf("NÃO");
        }
    }
    
    
}

/*Recebe uma matriz e a instância, ou seja, o "jogo do sudoku" que deve verificar,
retorna 0 errado e 1 para certo. */
int verificar_sudoku(int M[][9], int instancia){
    int inicio = 9 * (instancia - 1);
    int fim = inicio + 8;

    //Verifica as colunas e linhas atrás de repetidas
    //Começa a verificar de baixo para cima para evitar duplicatas (Checar A com B e B com A)
    for (int i = fim; i >= inicio; i--) {
        for (int j = 8; j >= 0; j--) {

            for (int n = inicio; n < i; n++) {
                if (M[i][j] == M[n][j]) return 0; 
            }
            for (int n = 0; n < j; n++) {
                if (M[i][j] == M[i][n]) return 0;
            }
            
        }
    }

    //Verifica os blocos 3x3
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){

            for (int n = inicio; n < i; n++) {
                if (M[i][j] == M[n][j]) return 0; 
            }
        }


    }
    return 1;
}