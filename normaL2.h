#ifndef __NORMAL2__
#define __NORMAL2__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "inversa.h"

float** calculaMatrizProduto(float** matrizA, float**  matrizB, int ordem);

float** subtraiMatrizes(float** matrizA, float** matrizB, int ordem);

void calculaNormaL2(float** matrizA, float** matrizInv, int ordem);

#endif