#ifndef SUM_H
#define SUM_H

#include <stdio.h>

int sum_array_normal(int * array, size_t size);

int sum_array_bitwise(int * array, size_t size);

int sum_array_cmov(int * array, size_t size);

#endif
