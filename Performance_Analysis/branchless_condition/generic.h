#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <time.h>

void print_arr(int *arr, int len);

int * rand_num_generator_int( int len , int max, int min);

int * array_copy(int * src, size_t size);

double time_diff_in_second(struct timespec t1, struct timespec t2);

void quick_sort(int a[], int l, int r);

int partition(int a[], int l, int r);

#endif
