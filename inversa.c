/*
MATEUS DOS SANTOS HERBELE
GRR20221254
*/
#include "inversa.h"


void mostraMatriz(double** matriz, int ordem){  
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("%.15e ", matriz[i][j]);
        }
        printf("\n");
    }
}


double** criaMatrizIdentidade(int ordem){
    double** matrizIdentidade = criaMatriz(ordem);
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            if(i == j){
                matrizIdentidade[i][j] = 1;
            } else {
                matrizIdentidade[i][j] = 0;
            }
        }
    }
    return matrizIdentidade;
}

double ** criaMatriz(int ordem){
    double** matriz = (double**)malloc(ordem * sizeof(double*));
    if(matriz == NULL){
        printf("Erro ao alocar memória para matriz\n");
        exit(1);
    }
    for(int i = 0; i < ordem; i++){
        matriz[i] = (double*)malloc(ordem * sizeof(double));
        if(matriz[i] == NULL){
            printf("Erro ao alocar memória para matriz[%d]'\n", i);
            exit(1);
        }
    }
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void liberarMatriz(double** matriz, int ordem){
    for(int i = 0; i < ordem; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void ajeitaMatrizL(double** matrizL, int ordem){
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            if(i == j){
                matrizL[i][j] = 1;
            } 
        }
    }
}

// Troca as linhas alterando os ponteiros
void trocaLinhas(double** matriz, double** matrizIdentidade, double** matrizL, int ordem, int linha1, int linha2){
    // Troca as linhas da matriz
    double* aux = matriz[linha1];
    matriz[linha1] = matriz[linha2];
    matriz[linha2] = aux;
    // Troca as linhas da matriz identidade
    aux = matrizIdentidade[linha1];
    matrizIdentidade[linha1] = matrizIdentidade[linha2];
    matrizIdentidade[linha2] = aux;
    // Troca as linhas da matriz L
    aux = matrizL[linha1];
    matrizL[linha1] = matrizL[linha2];
    matrizL[linha2] = aux;
}

// Pivoteamento
void pivoteamentoParcial(double** matriz, double** matrizIdentidade, double** matrizL, int ordem, int apartirDe){
    int maior = apartirDe; // A linha que tem o maior valor na coluna
    for(int i = apartirDe + 1; i < ordem; i++){
        if(abs(matriz[i][apartirDe]) > abs(matriz[maior][apartirDe])){
            maior = i;
        }
    }
    if(maior != apartirDe){
        trocaLinhas(matriz, matrizIdentidade, matrizL, ordem, apartirDe, maior);
    }
}

double** calculaInversa(double** matriz, int ordem){
    double** matrizU = matriz;
    double m = 0.0;
    double pivo = 0.0;
    double** matrizIdentidade = criaMatrizIdentidade(ordem);
    double** matrizL = criaMatriz(ordem);
    
    for(int i = 0; i < ordem; i++){
        pivoteamentoParcial(matrizU, matrizIdentidade, matrizL, ordem, i);
        pivo = matrizU[i][i];
        for(int j = i + 1; j < ordem; j++){
            m = matrizU[j][i] / pivo;
            matrizU[j][i] = 0.0;
            matrizL[j][i] = m;
            for(int k = i + 1; k < ordem; k++){
                matrizU[j][k] = matrizU[j][k] - (m * matrizU[i][k]);
            }
        }
    }
    ajeitaMatrizL(matrizL, ordem);
    return encontraInversa(matriz, matrizL, matrizIdentidade, ordem);    
}

double** encontraInversa(double** matrizU, double** matrizL, double** matrizIdentidade, int ordem){
    double* vetorY = (double*)malloc(ordem * sizeof(double));
    double* vetorX = (double*)malloc(ordem * sizeof(double));
    if(vetorY == NULL || vetorX == NULL){
        printf("Erro ao alocar memória para 'vetorY' ou 'vetorX'\n");
        exit(1);
    }
    double** matrizInversa = criaMatriz(ordem);

    for(int i = 0; i < ordem; i++){
        invRetroSubstituicao(matrizL, matrizIdentidade[i], vetorY, ordem);
        retroSubstituicao(matrizU, vetorY, vetorX, ordem);
        for(int j = 0; j < ordem; j++){
            matrizInversa[j][i] = vetorX[j];
        }
    }
    mostraMatriz(matrizInversa, ordem);
    free(vetorY);
    free(vetorX);
    liberarMatriz(matrizL, ordem);
    liberarMatriz(matrizIdentidade, ordem);
    return matrizInversa;
}

// Retro substituição para encontrar os valores de Y para calcular a inversa
void retroSubstituicao(double** matriz, double* igualdades, double* vetorResultado, int ordem){
    for (int i = ordem-1; i >= 0; --i) {
        vetorResultado[i] = igualdades[i];
        for (int j = i+1; j < ordem; ++j)
            vetorResultado[i] -= matriz[i][j] * vetorResultado[j];
        vetorResultado[i] /= matriz[i][i];
        }
}

// Retro substituição para encontrar os valores de X para calcular a inversa
// Como a matriz L é triangular superior, a retrosubstituição é de cima para baixo
void invRetroSubstituicao(double** matriz, double* igualdades, double* vetorResultado, int ordem){
    for(int i = 0; i < ordem; i++){
        vetorResultado[i] = igualdades[i];
        for(int j = 0; j < i; j++){
            vetorResultado[i] -= matriz[i][j] * vetorResultado[j];
        }
        vetorResultado[i] /= matriz[i][i];
    }
}
