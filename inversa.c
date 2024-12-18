/*
MATEUS DOS SANTOS HERBELE
GRR20221254
*/
#include <stdio.h>
#include <stdlib.h>
#include <likwid.h>
#include <fenv.h>
#include "calculaInversa.h"
#include "normaL2.h"
#include "utils.h"

int main(){
    LIKWID_MARKER_INIT;
  
    // Variáveis
    int ordem;
    rtime_t tempoInicial = 0;
    rtime_t tempoFinal = 0;
    double** matriz = NULL;
    double** matrizCopia = NULL;
    double** matrizInv = NULL;
    // Lê o tamanho da matriz
    scanf("%d", &ordem);
    printf("%d\n", ordem);
    // Aloca memória para a matriz
    matriz = criaMatriz(ordem);
    matrizCopia = criaMatriz(ordem);
    // Lê os elementos da matriz
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            scanf("%lf", &matriz[i][j]);
            matrizCopia[i][j] = matriz[i][j];
        }
    }

    fesetround(FE_DOWNWARD);
    // Marca o tempo inicial
    tempoInicial = timestamp();
    // Calcula a inversa
    LIKWID_MARKER_START("calcula-inversa");
    matrizInv = calculaInversa(matriz, ordem);
    LIKWID_MARKER_STOP("calcula-inversa");

    //Marca o tempo final
    tempoFinal = timestamp();

    calculaNormaL2(matrizCopia, matrizInv, ordem);
    printf("%.8e\n", tempoFinal - tempoInicial);

    // Libera a memória alocada
    for (int i = 0; i < ordem; i++) {
        free(matriz[i]);
        free(matrizCopia[i]);
        free(matrizInv[i]);
    }
    free(matriz);
    free(matrizCopia);
    free(matrizInv);

    LIKWID_MARKER_CLOSE;

    return 0;
}
