#include "inversa.h"


void mostraMatriz(float** matriz, int ordem){  
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("%.15e ", matriz[i][j]);
        }
        printf("\n");
    }
}


float** criaMatrizIdentidade(int ordem){
    float** matrizIdentidade = criaMatriz(ordem);
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

float ** criaMatriz(int ordem){
    float** matrizL = (float**)malloc(ordem * sizeof(float*));
    if(matrizL == NULL){
        printf("Erro ao alocar memória para matriz\n");
        exit(1);
    }
    for(int i = 0; i < ordem; i++){
        matrizL[i] = (float*)malloc(ordem * sizeof(float));
        if(matrizL[i] == NULL){
            printf("Erro ao alocar memória para matriz[%d]'\n", i);
            exit(1);
        }
    }
    return matrizL;
}

void ajeitaMatrizL(float** matrizL, int ordem){
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            if(i == j){
                matrizL[i][j] = 1;
            } 
        }
    }
}

// Troca as linhas alterando os ponteiros
void trocaLinhas(float** matriz, float** matrizIdentidade, float** matrizL, int ordem, int linha1, int linha2){
    // Troca as linhas da matriz
    float* aux = matriz[linha1];
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
void pivoteamentoParcial(float** matriz, float** matrizIdentidade, float** matrizL, int ordem, int apartirDe){
    int maior = apartirDe; // A linha que tem o maior valor na coluna
    for(int i = apartirDe + 1; i < ordem; i++){
        if(matriz[i][apartirDe] > matriz[maior][apartirDe]){
            maior = i;
        }
    }
    if(maior != matriz[apartirDe][apartirDe]){
        trocaLinhas(matriz, matrizIdentidade, matrizL, ordem, apartirDe, maior);
    }
}

float** calculaInversa(float** matriz, int ordem){
    float** matrizU = matriz;
    float m = 0.0;
    float pivo = 0.0;
    float** matrizIdentidade = criaMatrizIdentidade(ordem);
    float** matrizL = criaMatriz(ordem);
    
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

float** encontraInversa(float** matrizU, float** matrizL, float** matrizIdentidade, int ordem){
    float* vetorY = (float*)malloc(ordem * sizeof(float));
    float* vetorX = (float*)malloc(ordem * sizeof(float));
    if(vetorY == NULL || vetorX == NULL){
        printf("Erro ao alocar memória para 'vetorY' ou 'vetorX'\n");
        exit(1);
    }
    float** matrizInversa = criaMatriz(ordem);

    for(int i = 0; i < ordem; i++){
        invRetroSubstituicao(matrizL, matrizIdentidade[i], vetorY, ordem);
        retroSubstituicao(matrizU, vetorY, vetorX, ordem);
        for(int j = 0; j < ordem; j++){
            matrizInversa[j][i] = vetorX[j];
        }
    }
    mostraMatriz(matrizInversa, ordem);float** criaCopiaMatriz(float** matriz, int ordem){
    float** copiaMatriz = criaMatriz(ordem);
    for(int i = 0; i < ordem; i++){
        for(int j = 0; j < ordem; j++){
            copiaMatriz[i][j] = matriz[i][j];
        }
    }
    return copiaMatriz;
}
    return matrizInversa;
}

// Retro substituição para encontrar os valores de Y para calcular a inversa
void retroSubstituicao(float** matriz, float* igualdades, float* vetorResultado, int ordem){
    for (int i = ordem-1; i >= 0; --i) {
        vetorResultado[i] = igualdades[i];
        for (int j = i+1; j < ordem; ++j)
            vetorResultado[i] -= matriz[i][j] * vetorResultado[j];
        vetorResultado[i] /= matriz[i][i];
        }
}

// Retro substituição para encontrar os valores de X para calcular a inversa
// Como a matriz L é triangular superior, a retrosubstituição é de cima para baixo
void invRetroSubstituicao(float** matriz, float* igualdades, float* vetorResultado, int ordem){
    for(int i = 0; i < ordem; i++){
        vetorResultado[i] = igualdades[i];
        for(int j = 0; j < i; j++){
            vetorResultado[i] -= matriz[i][j] * vetorResultado[j];
        }
        vetorResultado[i] /= matriz[i][i];
    }
}
