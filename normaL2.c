/*
MATEUS DOS SANTOS HERBELE
GRR20221254
*/
#include "normaL2.h"

/*
matrizA = Matriz original do imput
matrizB = Matriz inversa calculada anteiormente
ordem = Ordem das matrizes
Função: Calcula o produto entre duas matrizes
*/
double** calculaMatrizProduto(double** matrizA, double** matrizB, int ordem){
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

/*
matriz = Matriz a ser subtraída
ordem = Ordem da matriz
Função: Subtrai 1 da diagonal principal da matriz, pois considera a subtração da matriz identidade
*/
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

/*
matrizA = Matriz original do input
matrizInv = Matriz inversa calculada anteriormente
ordem = Ordem das matrizes
Função: Calcula a norma L2 da matriz
*/

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