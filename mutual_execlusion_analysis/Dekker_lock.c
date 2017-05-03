/* Dekker's algorithm vs pthread_mutex_lock()
 *
 * USAGE: gcc -Wall --std=c99 -pthread Dekker_lock.c && ./a.out
 *
 * MACRO:
 *	_P: use pthread_mutex_lock()
 *	_D: use Dekker's algorithm to conduct lock.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <pthread.h>

#define mb() asm volatile("mfence":::"memory")
volatile char flag[2] = { false, false };
volatile char turn    = 0;

#ifdef _P
pthread_mutex_t mutex;
#endif

#define BIG_NUM 100000000
volatile long  global_value = 0;

static void * calc(void * arg)
{
	long countdown = BIG_NUM;

#ifdef _D
	int self  = *(int*) arg;
	int other = 1 - self;

	flag[self] = true;
	mb();
	while( flag[other] == true ) {
		if( turn != self ) {
			flag[self] = false;
			while( turn != self );
			flag[self] = true;
		}
	}
#elif _P
	pthread_mutex_lock(&mutex);

#endif
	/* critical section */
	while( countdown > 0 ) {
		countdown--;
		global_value++;
	}

#ifdef _D
	mb();
	turn = other;
	flag[self] = false;
#elif _P
	pthread_mutex_unlock(&mutex);
#endif

	return 0;
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

int main()
{
	int * input_1;
	int * input_2;
        double time_diff;
        struct timespec start, end;

#ifdef _P
	pthread_mutex_init(&mutex, NULL);
#endif

	pthread_t thread[2];

	input_1 = (int *) malloc( sizeof(int) );
	input_2 = (int *) malloc( sizeof(int) );

	* input_1 = 0;
	* input_2 = 1;

        clock_gettime(CLOCK_REALTIME, &start);

	pthread_create(&thread[0], NULL, &calc, (void *) input_1);
	pthread_create(&thread[1], NULL, &calc, (void *) input_2);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);

	clock_gettime(CLOCK_REALTIME, &end);

	printf("\tglobal_value: %lu\n", global_value);

        time_diff = time_diff_in_second(start, end);
        printf("\ttime difference in sencond: %lf\n", time_diff);
	return 0;
}
