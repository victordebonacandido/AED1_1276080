#include <stdio.h>

int main(){
    //Verify interval
    int N = 100, pos = 0;
    int X[N];
    for(int i = 0; i < N; i++){
        scanf("%d", &X[i]);
    }
    //Searching the smallest one
    for(int i = 0; i < N; i++){
       if(X[pos] <= X[i]) pos = i;
    }
    //Printing the result
    printf("%d\n", X[pos]);
    printf("%d\n", pos+1);
    return 0;
}
