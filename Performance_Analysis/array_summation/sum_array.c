
#include "sum_array.h"

/* The simplest method to do sum of array */
long sum_array_simplest(int * array, int length)
{
	unsigned i;
	int sum = 0;

	for ( i = 0; i < length; ++i ){
		sum += array[ i ];
	}
#ifdef __DEBUG
        printf("sum_array_simplest(): %d\n", sum);
#endif
	return sum;
}

/* The method unroll the loop to do sum array */
long sum_array_loop_unrolling(int * array, int length)
{
	unsigned i;
	int sum = 0;

	/* Loop unrolling. */
	for ( i = 0; i < length; i += 20 ) {
		sum += array[ i ];
		sum += array[ i + 1 ];
		sum += array[ i + 2 ];
		sum += array[ i + 3 ];
		sum += array[ i + 4 ];
		sum += array[ i + 5 ];
		sum += array[ i + 6 ];
		sum += array[ i + 7 ];
		sum += array[ i + 8 ];
		sum += array[ i + 9 ];
		sum += array[ i + 10];
		sum += array[ i + 11 ];
		sum += array[ i + 12 ];
		sum += array[ i + 13 ];
		sum += array[ i + 14 ];
		sum += array[ i + 15 ];
		sum += array[ i + 16 ];
		sum += array[ i + 17 ];
		sum += array[ i + 18 ];
		sum += array[ i + 19 ];
	}

	/* Add the remaining element. */
	for (; i < length; i++)
		sum += array[i];

#ifdef __DEBUG
        printf("sum_array_loop_unrolling(): %d\n", sum);
#endif
	return sum;
}

long sum_array_duffs_device(int * array, int length)
{
	unsigned i = 0;
	int sum = 0;
	int n = length;

	switch ( n % 10 ) {

		case 0: do {sum += array[ i++ ];
		case 9:     sum += array[ i++ ];
		case 8:     sum += array[ i++ ];
		case 7:     sum += array[ i++ ];
		case 6:     sum += array[ i++ ];
		case 5:     sum += array[ i++ ];
		case 4:     sum += array[ i++ ];
		case 3:     sum += array[ i++ ];
		case 2:     sum += array[ i++ ];
		case 1:     sum += array[ i++ ];

		} while ( (n -= 10) > 0 );
	}

#ifdef __DEBUG
        printf("sum_array_duffs_device(): %d\n", sum);
#endif
	return sum;
}
