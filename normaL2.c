#include "normaL2.h"

float** calculaMatrizProduto(float** matrizA, float**  matrizB, int ordem){
    float** matrizProduto = criaMatriz(ordem);
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            for(int k = 0; k < ordem; k++){
                matrizProduto[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    return matrizProduto;
}

float** subtraiMatrizes(float** matrizA, float** matrizB, int ordem){
    float** matrizSubtracao = criaMatriz(ordem);
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            matrizSubtracao[i][j] = matrizA[i][j] - matrizB[i][j];
        }
    }
    return matrizSubtracao;
}

void calculaNormaL2(float** matrizA, float** matrizInv, int ordem){
    float** matrizProduto = calculaMatrizProduto(matrizA, matrizInv, ordem);
    float** matrizIdentidade = criaMatrizIdentidade(ordem);
    float** matrizResiduo = subtraiMatrizes(matrizProduto, matrizIdentidade, ordem);
    float norma = 0.0;
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            norma += matrizResiduo[i][j] * matrizResiduo[i][j]; // Quadrado dos elementos do vetor
        }
    }
    norma = sqrt(norma);
    norma = norma/ordem;
    printf("%.15e\n", norma);
}