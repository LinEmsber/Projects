
#ifndef SUM_ARRAY_H
#define SUM_ARRAY_H

#include <stdio.h>
#include <stdlib.h>


/* functions */
long sum_array_simplest(int * array, int length);
long sum_array_loop_unrolling(int * array, int length);
long sum_array_duffs_device(int * array, int length);

#endif
