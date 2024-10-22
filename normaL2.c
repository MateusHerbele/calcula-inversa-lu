/*
MATEUS DOS SANTOS HERBELE
GRR20221254
*/
#include "normaL2.h"

double** calculaMatrizProduto(double** matrizA, double**  matrizB, int ordem){
    double** matrizProduto = criaMatriz(ordem);
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            for(int k = 0; k < ordem; k++){
                matrizProduto[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    return matrizProduto;
}

double** subtraiMatrizes(double** matriz, int ordem){
    double** matrizSubtracao = criaMatriz(ordem);
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            if(j == i)
                matrizSubtracao[i][j] = matriz[i][j] - 1.0;
            else
                matrizSubtracao[i][j] = matriz[i][j];
        }
    }
    return matrizSubtracao;
}

void calculaNormaL2(double** matrizA, double** matrizInv, int ordem){
    double** matrizResiduo = calculaMatrizProduto(matrizA, matrizInv, ordem);
    matrizResiduo = subtraiMatrizes(matrizResiduo, ordem);
    double norma = 0.0;
    double aux = 0.0;

    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++)
            aux += matrizResiduo[j][i] * matrizResiduo[j][i]; // Quadrado dos elementos do vetor
        aux = sqrt(aux);
        norma += aux;
        aux = 0.0;
    }
    norma = norma/ordem;
    printf("%.15e\n", norma);
    liberarMatriz(matrizResiduo, ordem);
}