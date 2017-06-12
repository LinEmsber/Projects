
#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <assert.h>

int * rn_arr_gen( int len , int start, int end);
void print_arr(int *arr, int len);
double time_diff_in_second(struct timespec t1, struct timespec t2);
void quick_sort( int v[], int left, int right);

#endif
