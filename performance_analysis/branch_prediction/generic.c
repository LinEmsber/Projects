
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generic.h"

#define XOR_SWAP_2(a, b) ( ( (a) == (b) ) || ( ( (a) ^= (b) ), ( (b) ^= (a) ), ( (a) ^= (b) ) ) )

/* generate a random number array in a specific range
 *
 * @len: the length of array
 * @start: the start number of array
 * @end: the end number of array
 */
int * rn_arr_gen( int len , int start, int end)
{
	int i;
	int * ret_arr = NULL;
	int range = start - end;

	// memroy allocation
	ret_arr = (int *) malloc( len * sizeof(int) );
	memset(ret_arr, 0, len + 1);

	// rand seed use time
	srand( (unsigned) time(NULL) );

	// generate arr
	for ( i = 0; i < len; i++ ){
		*(ret_arr + i) = (rand() % range) + 1;
	}

	return ret_arr;
}

/* print the array with specific lenght
 *
 * @arr: the target array
 * @len: the length of array
 */
void print_arr(int *arr, int len)
{
	int i;

	for ( i = 0; i < len; i++){
		printf("%d ", *(arr + i) );
	}
	printf("\n");
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

void swap(int v[], int i, int j)
{
	int tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}


void quick_sort( int v[], int left, int right)
{
	int i, last;

	// if the index of left element is equal or larger than the index of right element.
	if (left >= right)
		return;

	// swap the most left element with the middle element
	swap(v, left, (left + right) / 2);
	// assign the last index as the most left index (the middle index)
	last = left;

	for (i = left + 1; i <= right; i++){

		if (v[i] < v[left]){
			// last = last + 1;
			// swap(v, last, i);
			swap(v, ++last, i);
		}
	}

	swap(v, left, last);

	// quick sort the left side array
	quick_sort(v, left, last-1);
	// quick sort the right side array
	quick_sort(v, last+1, right);

}
