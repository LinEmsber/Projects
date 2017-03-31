/* branch prediction
 *
 * References:
 * http://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array
 * https://www.collabora.com/news-and-blog/blog/2017/03/21/performance-analysis-in-linux/
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <time.h>


int partition( int a[], int l, int r);

void print_arr(int *arr, int len)
{
        int i;

        for ( i = 0; i < len; i++)
                printf("%d ", *(arr + i) );

        printf("\n");
}

int * rand_num_generator_int( int len , int max, int min)
{
        int i;
        int * ret_arr = NULL;
        int range = max - min;

        // memroy allocation
        ret_arr = (int *) malloc( len * sizeof(int) );
        memset(ret_arr, 0, len + 1);

        // rand seed use time
        srand( (unsigned) time(NULL) );

        // generate arr
        for ( i = 0; i < len; i++ )
                *(ret_arr + i) = (rand() % range) + min;

        return ret_arr;
}


double time_diff_in_second(struct timespec t1, struct timespec t2)
{
	struct timespec diff;

	if (t2.tv_nsec - t1.tv_nsec < 0) {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	} else {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}

	return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}


void quick_sort( int a[], int l, int r)
{
        int j;

        if( l < r )
        {
                // divide and conquer
                j = partition( a, l, r);
                quick_sort( a, l, j-1);
                quick_sort( a, j+1, r);
        }

}

int partition( int a[], int l, int r)
{
        int pivot, i, j, t;
        pivot = a[l];
        i = l; j = r+1;

        while( 1)
        {
                do ++i; while( a[i] <= pivot && i <= r );
                do --j; while( a[j] > pivot );
                if( i >= j ) break;
                t = a[i]; a[i] = a[j]; a[j] = t;
        }
        t = a[l]; a[l] = a[j]; a[j] = t;
        return j;
}

int main()
{
	// array
	int *array;
	const int array_size = 327670;
	long long sum = 0;

	// time
	struct timespec start, end;
	double time_diff;

	// array generate
	array = rand_num_generator_int( array_size, 255, 0);
//	print_arr(array, array_size);

	// sorting
#ifdef _SORT
	quick_sort(array, 0, array_size - 1);
#endif

	// summation
	clock_gettime(CLOCK_REALTIME, &start);
	for (unsigned i = 0; i < 5000; ++i)
	{
		for (unsigned c = 0; c < array_size; ++c)
		{

#ifdef _NORMAL
			if (array[c] >= 128)
				sum += array[c];
#elif _BITWISE
			// int t = (array[c] - 128) >> 31;
			sum += ~(array[c] - 128) >> 31 & array[c];
#elif _CMOVGE
			sum += (array[c] >= 128) ? array[c] : 0;
#endif
		}
	}
	clock_gettime(CLOCK_REALTIME, &end);

	time_diff = time_diff_in_second(start, end);
	printf("\ttime difference in second: %lf\n", time_diff);
	printf("\tsum: %lld\n", sum);

	return 0;
}
