/*
MATEUS DOS SANTOS HERBELE
GRR20221254
*/
#ifndef __NORMAL2__
#define __NORMAL2__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "inversa.h"

double** calculaMatrizProduto(double** matrizA, double**  matrizB, int ordem);

double** subtraiMatrizes(double** matriz, int ordem);

void calculaNormaL2(double** matrizA, double** matrizInv, int ordem);

#endif