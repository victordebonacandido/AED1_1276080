#include <stdio.h>

int main(){
    //Verify interval
    int N = 0, pos = 0;
    while(N < 1 || N > 1000){
        scanf("%d", &N);
    }
    //Creating X
    int X[N];
    for(int i = 0; i < N; i++){
        scanf("%d", &X[i]);
    }
    //Searching the smallest one
    for(int i = 0; i < N; i++){
       if(X[pos] >= X[i]) pos = i;
    }
    //Printing the result
    printf("Menor valor: %d\n", X[pos]);
    printf("Posicao: %d\n", pos);
    return 0;
}