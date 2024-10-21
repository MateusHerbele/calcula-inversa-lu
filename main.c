#include <stdio.h>
#include <stdlib.h>
#include <likwid.h>
#include "inversa.h"
#include "normaL2.h"
#include "utils.h"

int main() {
    // Variáveis
  
    LIKWID_MARKER_INIT;
    LIKWID_MARKER_START("main");
  
    int ordem;
    rtime_t tempoInicial = 0;
    rtime_t tempoFinal = 0;
    float** matriz = NULL;
    float** matrizCopia = NULL;
    float** matrizInv = NULL;
    // Lê o tamanho da matriz
    scanf("%d", &ordem);

    // Aloca memória para a matriz
    matriz = criaMatriz(ordem);
    matrizCopia = criaMatriz(ordem);
    // Lê os elementos da matriz
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            scanf("%f", &matriz[i][j]);
            matrizCopia[i][j] = matriz[i][j];
        }
    }

    // Marca o tempo inicial
    tempoInicial = timestamp();
    // Calcula a inversa
    matrizInv = calculaInversa(matriz, ordem);
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

    LIKWID_MARKER_STOP("main");
    LIKWID_MARKER_CLOSE;

    return 0;
}
