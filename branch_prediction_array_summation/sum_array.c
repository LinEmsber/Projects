
#include "sum_array.h"

/* The simplest method to do sum of array */
int sum_array_simplest(int * array, int length)
{
	int i;
	int sum;

	for ( i = 0; i < length; ++i ){
		sum += array[ i ];
	}

	return sum;
}

/* The method unroll the loop to do sum array */
int sum_array_unroll(int * array, int length)
{
	int i;
	int sum;

	// for ( i = 0; i < length; i += 10 ) {
	// 	sum += array[ i ];
	// 	sum += array[ i + 1 ];
	// 	sum += array[ i + 2 ];
	// 	sum += array[ i + 3 ];
	// 	sum += array[ i + 4 ];
	// 	sum += array[ i + 5 ];
	// 	sum += array[ i + 6 ];
	// 	sum += array[ i + 7 ];
	// 	sum += array[ i + 8 ];
	// 	sum += array[ i + 9 ];
	// }

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

	return sum;
}

int sum_array_duffs_device(int * array, int length)
{
	int i = 0;
	int sum;
	int n = length;

	switch ( n % 5 ) {

		case 0: do {sum += array[ i++ ];
		case 4:     sum += array[ i++ ];
		case 3:     sum += array[ i++ ];
		case 2:     sum += array[ i++ ];
		case 1:     sum += array[ i++ ];

		} while ( (n -= 5) > 0 );
        }

	// switch ( n % 10 ) {
	//
	// 	case 0: do {sum += array[ i++ ];
	// 	case 9:     sum += array[ i++ ];
	// 	case 8:     sum += array[ i++ ];
	// 	case 7:     sum += array[ i++ ];
	// 	case 6:     sum += array[ i++ ];
	// 	case 5:     sum += array[ i++ ];
	// 	case 4:     sum += array[ i++ ];
	// 	case 3:     sum += array[ i++ ];
	// 	case 2:     sum += array[ i++ ];
	// 	case 1:     sum += array[ i++ ];
	//
	// 	} while ( (n -= 10) > 0 );
	// }

	return sum;
}
