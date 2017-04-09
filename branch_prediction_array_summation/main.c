

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "sum_array.h"
#include "generic.h"

// the length of array
#define RAND_NUMS 100

// how many times to add array
#define RUN_TIMES 1000000


/* global variables */
int sum_simplest = 0;
int sum_unroll = 0;
int sum_duffs_device = 0;


int main(int argc, char *argv[])
{
	int i;
	double time_diff_1 = 0, time_diff_2 = 0, time_diff_3 = 0;
	struct timespec start_1, end_1, start_2, end_2, start_3, end_3;

	int * array = rn_arr_gen( RAND_NUMS, 0, 1000 );
	quick_sort(array, 0, RAND_NUMS);

	/* simplest */
	clock_gettime(CLOCK_REALTIME, &start_1);
	for ( i = 0; i < RUN_TIMES ; i++ ){
		sum_simplest = sum_array_simplest(array, RAND_NUMS);
		sum_simplest = 0;
	}
	clock_gettime(CLOCK_REALTIME, &end_1);
	time_diff_1 = time_diff_in_second(start_1, end_1);

	/* unroll loop */
	clock_gettime(CLOCK_REALTIME, &start_2);
	for ( i = 0; i < RUN_TIMES ; i++ ){

		sum_unroll = sum_array_unroll(array, RAND_NUMS);
		sum_unroll = 0;
	}
	clock_gettime(CLOCK_REALTIME, &end_2);
	time_diff_2 = time_diff_in_second(start_2, end_2);

	/* duffs device */
	clock_gettime(CLOCK_REALTIME, &start_3);
	for ( i = 0; i < RUN_TIMES ; i++ ){
		sum_duffs_device = sum_array_duffs_device(array, RAND_NUMS);
		sum_duffs_device = 0;
	}
	clock_gettime(CLOCK_REALTIME, &end_3);
	time_diff_3 = time_diff_in_second(start_3, end_3);

	printf("simplest, time difference in sencond: %lf\n", time_diff_1);
	printf("unroll, time difference in sencond: %lf\n", time_diff_2);
	printf("duffs device, time difference in sencond: %lf\n", time_diff_3);

	free(array);

	return 0;
}
