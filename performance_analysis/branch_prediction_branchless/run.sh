#!/bin/bash

# optimization level
# http://www.rapidtables.com/code/linux/gcc/gcc-o.htm

echo "NORMAL"
gcc -O2 -D_NORMAL branchless.c && ./a.out
echo ""

echo "BITWISE"
gcc -O2 -D_BITWISE branchless.c  && ./a.out
echo ""

echo "CMOVGE"
gcc -O2 -D_CMOVGE -masm=intel branchless.c && ./a.out
echo ""

echo "NORMAL and SORT"
gcc -O2 -D_NORMAL branchless.c -D_SORT && ./a.out
echo ""

echo "BITWISE and SORT"
gcc -O2 -D_BITWISE branchless.c  -D_SROT && ./a.out
echo ""

echo "CMOVGE and SORT"
gcc -O2 -D_CMOVGE -masm=intel branchless.c -D_SROT && ./a.out
echo ""
