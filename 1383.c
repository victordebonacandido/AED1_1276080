/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 20/08/2026
Objetivo    : Verificar N instâncias de Sudokus e devolver se a resolução é certa ou errada
Uso da IA   : Usei a IA para verificar se o código estava funcionando adequadamente e para me ajudar
              na lógica da verificação dos blocos 3x3 que não estava conseguindo colocar a minha lógica
              no código.
-------------------------------------------------------------------------- */

#include <stdio.h>

int verificar_sudoku(int M[][9], int instancia);

int main(){
    int num_matriz = 0;
    
    
    scanf("%d", &num_matriz);

    // Escaneia os elementos das matrizes
    int M[9*num_matriz][9];
    for(int i = 0; i < 9*num_matriz; i++){
        for(int j = 0; j < 9; j++){
            scanf("%d", &M[i][j]);
        }
    }

    // Verifica as instâncias e imprime o resultado
    for(int vezes = 1; vezes <= num_matriz; vezes++){
        
        printf("Instancia %d\n", vezes);
        
        if(verificar_sudoku(M, vezes)){
            printf("SIM\n\n");
        }
        else{
            printf("NAO\n\n");
        }
    }
    
    return 0; 
}

/* Recebe uma matriz e a instância, retorna 0 (errado) ou 1 (certo). */
int verificar_sudoku(int M[][9], int instancia){
    int inicio = 9 * (instancia - 1);
    int fim = inicio + 8;

    // Verifica as colunas e linhas
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

    // Verifica os blocos 3x3 usando vetor de frequência
    for (int bloco_i = inicio; bloco_i <= fim; bloco_i += 3) {
        for (int bloco_j = 0; bloco_j < 9; bloco_j += 3) {
            
            int usado[10] = {0}; 
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int valor = M[bloco_i + i][bloco_j + j];
                    
                    //Checagem de segurança (valor fora de 1-9 ou repetido)
                    if (valor < 1 || valor > 9 || usado[valor] == 1) return 0; 
                    usado[valor] = 1; 
                }
            }
        }
    }
    
    return 1;
}