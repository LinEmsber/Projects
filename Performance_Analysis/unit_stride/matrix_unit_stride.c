/* The demonstration of the unit stride will impact the speed of the program.
 *
 * We use the same matrix, but use the different stride to assign the value.
 * Finally, the total time spend is different, and we also use perf to observe the details of the program.
 *
 * We can find that the cache-misses increasing, if the stride of the matrix is large.
 */

#include <stdio.h>
#include <stdlib.h>

#define RUN_TIMES 1000
#define MATRIX_LEN 1000

int main()
{
	int k;
	int i, j;
	int a[MATRIX_LEN][MATRIX_LEN];

	/* In general, Method 1 is faster because it accesses memory with unit stride,
	 * which is much more cache-efficient than Method 2, which has a stride of MATRIX_LEN.
	 *
	 * Method 1:
	 *
	 * [ ][ ][ ][ ][ ] ....
	 * ^1st assignment
	 *    ^2nd assignment
	 * [ ][ ][ ][ ][ ] ....
	 * ^101st assignment
	 *
	 * Method 2:
	 *
	 * [ ][ ][ ][ ][ ] ....
	 * ^1st assignment
	 *    ^101st assignment
	 * [ ][ ][ ][ ][ ] ....
	 * ^2nd assignment
	 */
	for (k = 0; k < RUN_TIMES; k++ ){

#ifdef _I
		/* Method 1 */
		for(i = 0; i < MATRIX_LEN; i++)
			for(j = 0; j < MATRIX_LEN; j++)
				a[i][j] = k;
#elif _J
		/* Method 2 */
		for(i = 0; i < MATRIX_LEN; i++)
			for(j = 0; j < MATRIX_LEN; j++)
				a[j][i] = k;
#endif

	}

	return 0;
}
