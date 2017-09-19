

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "sum_array.h"
#include "generic.h"

// the length of array
#define RAND_NUMS 152133

// how many times to add array
#ifdef __DEBUG
#define RUN_TIMES 1
#else
#define RUN_TIMES 10000
#endif

int main(int argc, char *argv[])
{
	unsigned int i;
	int sum_simplest = 0;
	int sum_loop_unrolling = 0;
	int sum_duffs_device = 0;
	double time_diff_1 = 0, time_diff_2 = 0, time_diff_3 = 0;
	struct timespec start_1, end_1, start_2, end_2, start_3, end_3;

	int * array = rn_arr_gen( RAND_NUMS, 0, 1000 );
	// quick_sort(&array, 0, RAND_NUMS);
	merge_sort(array, RAND_NUMS);

	/* Simplest. */
	clock_gettime(CLOCK_REALTIME, &start_1);
	for ( i = 0; i < RUN_TIMES ; i++ ){
		sum_simplest = sum_array_simplest(array, RAND_NUMS);
#ifdef __DEBUG
		printf("sum_simplest: %d\n", sum_simplest);
#endif
		sum_simplest = 0;
	}
	clock_gettime(CLOCK_REALTIME, &end_1);
	time_diff_1 = time_diff_in_second(start_1, end_1);
	printf("Simplest summation, time difference in sencond: %lf\n", time_diff_1);

	/* Loop unrolling. */
	clock_gettime(CLOCK_REALTIME, &start_2);
	for ( i = 0; i < RUN_TIMES ; i++ ){
		sum_loop_unrolling = sum_array_loop_unrolling(array, RAND_NUMS);
#ifdef __DEBUG
		printf("sum_loop_unrolling: %d\n", sum_loop_unrolling);
#endif
		sum_loop_unrolling = 0;
	}
	clock_gettime(CLOCK_REALTIME, &end_2);
	time_diff_2 = time_diff_in_second(start_2, end_2);
	printf("Loop unrolling, time difference in sencond: %lf\n", time_diff_2);

	/* Duff's device. */
	clock_gettime(CLOCK_REALTIME, &start_3);
	for ( i = 0; i < RUN_TIMES ; i++ ){
		sum_duffs_device = sum_array_duffs_device(array, RAND_NUMS);
#ifdef __DEBUG
		printf("sum_duffs_device: %d\n", sum_duffs_device);
#endif
		sum_duffs_device = 0;
	}
	clock_gettime(CLOCK_REALTIME, &end_3);
	time_diff_3 = time_diff_in_second(start_3, end_3);
	printf("Duff's device, time difference in sencond: %lf\n", time_diff_3);

	free(array);

	return 0;
}
