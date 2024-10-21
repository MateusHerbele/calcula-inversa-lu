#ifndef __INVERSA__
#define __INVERSA__

#include <stdio.h>
#include <stdlib.h>

void mostraMatriz(float** matriz, int ordem);

float** criaMatrizIdentidade(int ordem);

float ** criaMatriz(int ordem);

void liberarMatriz(float** matriz, int ordem);

void ajeitaMatrizL(float** matrizL, int ordem);

float** calculaInversa(float** matriz, int ordem);

void trocaLinhas(float** matriz, float** matrizIdentidade, float** matrizL, int ordem, int linha1, int linha2);

void pivoteamentoParcial(float** matriz, float** matrizIdentidade, float** matrizL, int ordem, int apartirDe);
// encontrar melhor nome pra essa função de baixo
float** encontraInversa(float** matrizU, float** matrizL, float** matrizIdentidade, int ordem);

void retroSubstituicao(float** matriz, float* igualdades, float* vetorResultado, int ordem);

void invRetroSubstituicao(float** matriz, float* igualdades, float* vetorResultado, int ordem);

#endif