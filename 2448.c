/* --------------------------------------------------------------------------
Disciplina  : Algoritmo e Estrutura de Dados 2026S1
Nome        : Victor de Bona Cândido
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/2448
Data        : 22/09/2026
Objetivo    : Receber o número de casas e encomendas e calcular quanto tempo para entregar tudo
Uso da IA   : Usei IA para verificar o código
-------------------------------------------------------------------------- */



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int busca_binaria(int x, int tam, int *v);

int main(){
    int num_casas, num_pedidos, tempo = 0, inicio = 0;
    scanf("%d %d", &num_casas, &num_pedidos);
    int casas[num_casas], ordem[num_pedidos];

    for(int i = 0; i < num_casas; i++){
        scanf("%d", &casas[i]);
    }

    for(int i = 0; i < num_pedidos; i++){
        scanf("%d", &ordem[i]);
    }

    for(int i = 0; i < num_pedidos;  i++){
        tempo += abs(inicio - busca_binaria(ordem[i], num_casas, casas));
        inicio = busca_binaria(ordem[i], num_casas, casas);
    }
    printf("%d\n", tempo);

    return 0;
}

int busca_binaria(int x, int tam, int *v){
    int e, m, d;
    e = -1, d = tam;
    while(e < d-1){
        m = (e+d)/2;
        if(v[m] > x) d = m;
        else e = m;
    }
    return e;
}

