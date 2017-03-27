/*

Using Gprof or perf to conduct an analysis of array summation.
We use different summation algorithms to compare the resources use.

-------------------------------------------------------------------------------
Usage and explanation:
-------------------------------------------------------------------------------

Gprof:

1. compile it, remember to add option "-pg" for gporf, and "-O0" for default optimization for
compilation time.
> gcc -O0 -Wall -pg sum_array_01.c

2. After we compile the output file, we MUST to run this program once to create a file, gmont.out,
for analysis.
> ./a.out

3. run Gprof to analyze the result.
> gprof -b ./a.out gmon.out

or
> gcc -O0 -Wall -pg sum_array_01.c && ./a.out && gprof -b ./a.out gmon.out


Perf:

compile it
> gcc -O0 -Wall -g sum_array_01.c

1. find which function have the most branch-misses?
perf with option "-e" to specify the events: branch-misses, branch-instructions

> gcc -O0 -Wall -pg sum_array_01.c && sudo perf record -e branch-misses:u,branch-instructions:u ./a.out && sudo perf report

2. find the most overhead functions
add doller sign behind executiable binary, and perf with option "-p" to specify PID.
$! is the PID of the most recent background command.

> gcc -O0 -Wall -pg sum_array_01.c && ./a.out & sudo perf top -p $!

TODO:
use faster method (better algorithms) to do array summing.
add time diff
multi-thread


References:
http://os.51cto.com/art/200703/41426.htm
https://www.ptt.cc/bbs/C_and_CPP/M.1246071002.A.A54.html
https://en.wikipedia.org/wiki/Duff's_device
http://www.rapidtables.com/code/linux/gcc/gcc-o.htm
https://embedded2016.hackpad.com/ep/pad/static/YkqjhwgnQcA

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <assert.h>

// the length of array
#define RAND_NUMS 10000000

// how many times to add array
#define RUN_TIMES 1

// global variables
int sum_simplest = 0;
int sum_reduces_brances = 0;
int sum_duffs_device = 0;

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


/* The simplest method to do sum of array */
int sum_array_simplest(int * array)
{
	int i;
	for ( i = 0; i < RAND_NUMS; ++i ){
		sum_simplest += array[ i ];
	}
	// printf("sum_simplest: %d\n", sum_simplest);
	return sum_simplest;
}

/* The method which reduces the brances to do sum array */
int sum_array_reduces_brances(int * array)
{
	int i;
	for ( i = 0; i < RAND_NUMS; i += 10 ) {
		sum_reduces_brances += array[ i ];
		sum_reduces_brances += array[ i + 1 ];
		sum_reduces_brances += array[ i + 2 ];
		sum_reduces_brances += array[ i + 3 ];
		sum_reduces_brances += array[ i + 4 ];
		sum_reduces_brances += array[ i + 5 ];
		sum_reduces_brances += array[ i + 6 ];
		sum_reduces_brances += array[ i + 7 ];
		sum_reduces_brances += array[ i + 8 ];
		sum_reduces_brances += array[ i + 9 ];
	}

	// for ( i = 0; i < RAND_NUMS; i += 20 ) {
	// 	sum_reduces_brances += array[ i ];
	// 	sum_reduces_brances += array[ i + 1 ];
	// 	sum_reduces_brances += array[ i + 2 ];
	// 	sum_reduces_brances += array[ i + 3 ];
	// 	sum_reduces_brances += array[ i + 4 ];
	// 	sum_reduces_brances += array[ i + 5 ];
	// 	sum_reduces_brances += array[ i + 6 ];
	// 	sum_reduces_brances += array[ i + 7 ];
	// 	sum_reduces_brances += array[ i + 8 ];
	// 	sum_reduces_brances += array[ i + 9 ];
	// 	sum_reduces_brances += array[ i + 10];
	// 	sum_reduces_brances += array[ i + 11 ];
	// 	sum_reduces_brances += array[ i + 12 ];
	// 	sum_reduces_brances += array[ i + 13 ];
	// 	sum_reduces_brances += array[ i + 14 ];
	// 	sum_reduces_brances += array[ i + 15 ];
	// 	sum_reduces_brances += array[ i + 16 ];
	// 	sum_reduces_brances += array[ i + 17 ];
	// 	sum_reduces_brances += array[ i + 18 ];
	// 	sum_reduces_brances += array[ i + 19 ];
	// }
	// printf("sum_reduces_brances: %d\n", sum_reduces_brances);
	return sum_reduces_brances;
}

int sum_array_duffs_device(int * array)
{
	int i = 0;
	int n = RAND_NUMS;

	// switch ( n % 5 ) {
	//
	// 	case 0: do {sum_duffs_device += array[ i++ ];
	// 	case 4:     sum_duffs_device += array[ i++ ];
	// 	case 3:     sum_duffs_device += array[ i++ ];
	// 	case 2:     sum_duffs_device += array[ i++ ];
	// 	case 1:     sum_duffs_device += array[ i++ ];
	//
	// 	} while ( (n -= 5) > 0 );
        // }
	switch ( n % 10 ) {

		case 0: do {sum_duffs_device += array[ i++ ];
		case 9:     sum_duffs_device += array[ i++ ];
		case 8:     sum_duffs_device += array[ i++ ];
		case 7:     sum_duffs_device += array[ i++ ];
		case 6:     sum_duffs_device += array[ i++ ];
		case 5:     sum_duffs_device += array[ i++ ];
		case 4:     sum_duffs_device += array[ i++ ];
		case 3:     sum_duffs_device += array[ i++ ];
		case 2:     sum_duffs_device += array[ i++ ];
		case 1:     sum_duffs_device += array[ i++ ];

		} while ( (n -= 10) > 0 );
	}
        // printf("sum_duffs_device: %d\n", sum_duffs_device);
	return sum_duffs_device;
}

void check_array_summation(int * array)
{
	// run differet methods to sum array, and check those sum are the same.
	sum_simplest = sum_array_simplest(array);
	sum_reduces_brances = sum_array_reduces_brances(array);
	sum_duffs_device = sum_array_duffs_device(array);

	// reset global variable
	sum_simplest = 0;
	sum_reduces_brances = 0;
	sum_duffs_device = 0;
}


int main(int argc, char *argv[])
{
	int i;

	int * array = rn_arr_gen( RAND_NUMS, 0, 10 );
	// print_arr( array, RAND_NUMS );

	for ( i = 0; i < RUN_TIMES ; i++ ){

		// run differet methods to sum array, and check those sum are the same.
		sum_simplest = sum_array_simplest(array);
		sum_duffs_device = sum_array_duffs_device(array);
		sum_reduces_brances = sum_array_reduces_brances(array);

		// reset global variable
		sum_simplest = 0;
		sum_reduces_brances = 0;
		sum_duffs_device = 0;
	}

	free(array);

	return 0;
}
