#!/bin/bash

# gcc -O0 -D_I matrix_unit_stride.c
# perf stat -e cache-misses,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses ./a.out
#
# gcc -O0 -D_J matrix_unit_stride.c
# perf stat -e cache-misses,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-stores,L1-icache-load-misses ./a.out

gcc -O0 -D_I matrix_unit_stride.c && perf stat ./a.out
gcc -O0 -D_J matrix_unit_stride.c && perf stat ./a.out

# gcc -O3 -D_I matrix_unit_stride.c && perf stat ./a.out
# gcc -O3 -D_J matrix_unit_stride.c && perf stat ./a.out
