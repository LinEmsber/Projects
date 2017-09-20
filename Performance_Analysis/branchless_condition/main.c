
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <time.h>

#include "sum.h"
#include "generic.h"

#define SUM_TIMES 1000

int main()
{
	int * array_original = NULL;
        int * array_sorted = NULL;
	const int array_size = 327670;
        // const int array_size = 10;
	long long total_sum_normal = 0;
        long long total_sum_normal_sort = 0;
        long long total_sum_bitwise = 0;
        long long total_sum_bitwise_sort = 0;
        long long total_sum_comvge = 0;
        long long total_sum_comvge_sort = 0;

	struct timespec start_normal, end_normal;
        struct timespec start_normal_sort, end_normal_sort;
        struct timespec start_bitwise, end_bitwise;
        struct timespec start_bitwise_sort, end_bitwise_sort;
        struct timespec start_comvge, end_comvge;
        struct timespec start_comvge_sort, end_comvge_sort;

	double time_diff_normal;
        double time_diff_normal_sort;
        double time_diff_bitwise;
        double time_diff_bitwise_sort;
        double time_diff_comvge;
        double time_diff_comvge_sort;

	array_original = rand_num_generator_int(array_size, 255, 0);
        array_sorted = array_copy(array_original, array_size);

	quick_sort(array_sorted, 0, array_size - 1);

	/* NORMAL. */
	clock_gettime(CLOCK_REALTIME, &start_normal);

	for (unsigned i = 0; i < SUM_TIMES; ++i)
                total_sum_normal += sum_array_normal(array_original, array_size);

	clock_gettime(CLOCK_REALTIME, &end_normal);
        time_diff_normal = time_diff_in_second(start_normal, end_normal);
	printf("NORMAL\n");
        printf("\ttime difference in second: %lf\n", time_diff_normal);
        printf("\tsum: %lld\n", total_sum_normal);

	/* BITWISE. */
        clock_gettime(CLOCK_REALTIME, &start_bitwise);

	for (unsigned i = 0; i < SUM_TIMES; ++i)
                total_sum_bitwise += sum_array_bitwise(array_original, array_size);

	clock_gettime(CLOCK_REALTIME, &end_bitwise);
        time_diff_bitwise = time_diff_in_second(start_bitwise, end_bitwise);
	printf("BITWISE\n");
        printf("\ttime difference in second: %lf\n", time_diff_bitwise);
        printf("\tsum: %lld\n", total_sum_bitwise);

	/* CMOV. */
        clock_gettime(CLOCK_REALTIME, &start_comvge);

	for (unsigned i = 0; i < SUM_TIMES; ++i)
                total_sum_comvge += sum_array_cmov(array_original, array_size);

	clock_gettime(CLOCK_REALTIME, &end_comvge);
        time_diff_comvge = time_diff_in_second(start_comvge, end_comvge);
	printf("CMOV\n");
        printf("\ttime difference in second: %lf\n", time_diff_comvge);
        printf("\tsum: %lld\n", total_sum_comvge);


	/* NORMAL with sorting. */
	clock_gettime(CLOCK_REALTIME, &start_normal_sort);

	for (unsigned i = 0; i < SUM_TIMES; ++i)
		total_sum_normal_sort += sum_array_normal(array_sorted, array_size);

	clock_gettime(CLOCK_REALTIME, &end_normal_sort);

	time_diff_normal_sort = time_diff_in_second(start_normal_sort, end_normal_sort);
	printf("NORMAL with sorting\n");
	printf("\ttime difference in second: %lf\n", time_diff_normal_sort);
	printf("\tsum: %lld\n", total_sum_normal_sort);

	/* BITWISE with sorting. */
	clock_gettime(CLOCK_REALTIME, &start_bitwise_sort);

	for (unsigned i = 0; i < SUM_TIMES; ++i)
		total_sum_bitwise_sort += sum_array_bitwise(array_sorted, array_size);

	clock_gettime(CLOCK_REALTIME, &end_bitwise_sort);

	time_diff_bitwise_sort = time_diff_in_second(start_bitwise_sort, end_bitwise_sort);
	printf("BITWISE with sorting\n");
	printf("\ttime difference in second: %lf\n", time_diff_bitwise_sort);
	printf("\tsum: %lld\n", total_sum_bitwise_sort);

	/* CMOV with sorting. */
	clock_gettime(CLOCK_REALTIME, &start_comvge_sort);

	for (unsigned i = 0; i < SUM_TIMES; ++i)
		total_sum_comvge_sort += sum_array_cmov(array_sorted, array_size);

	clock_gettime(CLOCK_REALTIME, &end_comvge_sort);

	time_diff_comvge_sort = time_diff_in_second(start_comvge_sort, end_comvge_sort);
	printf("CMOV with sorting\n");
	printf("\ttime difference in second: %lf\n", time_diff_comvge_sort);
	printf("\tsum: %lld\n", total_sum_comvge_sort);

	return 0;
}
