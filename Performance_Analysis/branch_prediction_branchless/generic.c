#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <unistd.h>
#include <time.h>

#include "generic.h"

void print_arr(int *arr, int len)
{
        unsigned int i;

        for ( i = 0; i < len; i++)
                printf("%d ", *(arr + i) );

        printf("\n");
}

int * rand_num_generator_int( int len , int max, int min)
{
        unsigned int i;
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

int * array_copy(int * src, size_t size)
{
        int * dest = (int *) malloc (size * sizeof(int));
        memcpy(dest, src, sizeof(int) * size);

        return dest;
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


void quick_sort(int a[], int l, int r)
{
        unsigned int j;

        if( l < r )
        {
                // divide and conquer
                j = partition( a, l, r);
                quick_sort( a, l, j-1);
                quick_sort( a, j+1, r);
        }

}

int partition(int a[], int l, int r)
{
        unsigned int pivot, i, j, t;
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
