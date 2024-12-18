#!/bin/bash

#MATEUS DOS SANTOS HERBELE
#GRR20221254

# Nome do arquivo de saída temporário
OUTPUT_TEMP="temp.txt"

# Executa o likwid-perfctr
likwid-perfctr -C 3 -g FLOPS_DP -O -o $OUTPUT_TEMP -m ./inversa

# Filtra as informações
FP_ARITH_INST=$(cat $OUTPUT_TEMP | grep -E "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE" | awk -F, '{print $3}')
DP_MFLOPS=$(cat $OUTPUT_TEMP | grep -E "DP \[MFLOP/s\]" | awk -F, '{print $2}')

# Exibe as informações
{
echo "FP_ARITH_INST_RETIRED_SCALAR_DOUBLE, $FP_ARITH_INST"
echo "DP [MFLOP/s], $DP_MFLOPS"
}| grep -v '^0$'

# Remove o arquivo temporário
rm temp.txt