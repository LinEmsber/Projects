/* An implementation of array summing using Gprof to do a analysis. */

/* Usage and explanation

1. compile it, remeber to add option "-pg"
> gcc -Wall -pg gprof_sum_array_01.c

2. MUST to run once to create a file, gmont.out, for analyze
> ./a.out

3. run Gprof to analyze your result
> gprof -b ./a.out gmon.out

COMBO:
> gcc -Wall -pg gprof_sum_array_01.c && ./a.out && gprof -b ./a.out gmon.out


TODO:
1. understand what is assert().
2. try to do a Makefile for this project.
3. use faster method (better algorithms) to do array summing.
4. multi-thread

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <assert.h>

#define RAND_NUMS 100000
#define RUN_TIMES 100000

// global variables
int sum_a = 0;
int sum_b = 0;

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
                sum_a += array[ i ];
        }
        // printf("sum_a: %d\n", sum_a);
        return sum_a;
}

/* The method which reduces the brances to do sum array */
int sum_array_reduces_brances(int * array)
{
        int i;
        for ( i = 0; i < RAND_NUMS; i += 20 ) {
                sum_b += array[ i ];
                sum_b += array[ i + 1 ];
                sum_b += array[ i + 2 ];
                sum_b += array[ i + 3 ];
                sum_b += array[ i + 4 ];
                sum_b += array[ i + 5 ];
                sum_b += array[ i + 6 ];
                sum_b += array[ i + 7 ];
                sum_b += array[ i + 8 ];
                sum_b += array[ i + 9 ];
                sum_b += array[ i + 10];
                sum_b += array[ i + 11 ];
                sum_b += array[ i + 12 ];
                sum_b += array[ i + 13 ];
                sum_b += array[ i + 14 ];
                sum_b += array[ i + 15 ];
                sum_b += array[ i + 16 ];
                sum_b += array[ i + 17 ];
                sum_b += array[ i + 18 ];
                sum_b += array[ i + 19 ];
        }
        // printf("sum_b: %d\n", sum_b);
        return sum_b;
}

void check_two_array_sum(int * array)
{
        // run two differet method to sum array, and check the both sum are the same.
        assert( sum_array_simplest(array) == sum_array_reduces_brances(array) );

        // reset sum_a and sum_b
        sum_a = 0;
        sum_b = 0;
}


int main(int argc, char *argv[])
{
	int i;

        int * array = rn_arr_gen( RAND_NUMS, 0, 99 );
        // print_arr( array, RAND_NUMS );

	for ( i = 0; i < RUN_TIMES; i++ ){
		check_two_array_sum(array);
	}

}
