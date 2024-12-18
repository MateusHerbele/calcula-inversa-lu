/*
MATEUS DOS SANTOS HERBELE
GRR20221254
*/
#ifndef __CALCULA_INVERSA__
#define __CALCULA_INVERSA__

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void mostraMatriz(double** matriz, int ordem);

double** criaMatrizIdentidade(int ordem);

double ** criaMatriz(int ordem);

void liberarMatriz(double** matriz, int ordem);

void ajeitaMatrizL(double** matrizL, int ordem);

double** calculaInversa(double** matriz, int ordem);

double** encontraInversa(double** matrizU, double** matrizL, double** matrizIdentidade, int ordem);

void trocaLinhas(double** matriz, double** matrizIdentidade, double** matrizL, int ordem, int linha1, int linha2);

void pivoteamentoParcial(double** matriz, double** matrizIdentidade, double** matrizL, int ordem, int apartirDe);

void retroSubstituicao(double** matriz, double* igualdades, double* vetorResultado, int ordem);

void invRetroSubstituicao(double** matriz, double* igualdades, double* vetorResultado, int ordem);

#endif