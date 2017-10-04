/* Dekker's algorithm Petersion's algorithm vs pthread_mutex_lock()
 *
 * USAGE: gcc -Wall -pthread -D mutex_lock_test.c && ./a.out
 *
 * MACRO:
 *	_PTHREAD: use pthread_mutex_lock()
 *	_D: use Dekker's algorithm to conduct lock.
 *	_P: use Peterson's algorithm to conduct lock.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <pthread.h>

#define BIG_NUM 500000000

long  global_value = 0;

int flag[2];
int turn;

#ifdef _PTHREAD
pthread_mutex_t mutex;
#endif

/* Functions of Dekker's lock. */
void d_lock_init()
{
	flag[0] = flag[1] = 0;
	turn = 0;
}

void d_lock(int _self, int _other)
{
	flag[_self] = true;

	while( flag[_other] == true ) {
		if( turn != _self ) {
			flag[_self] = false;
			while( turn != _self );
			flag[_self] = true;
		}
	}
}

void d_unlock(int _self, int _other)
{
	turn = _other;
	flag[_self] = false;
}



/* Functions of Peterson's lock. */
void p_lock_init()
{
	flag[0] = flag[1] = 0;
	turn = 0;
}

void p_lock(int self)
{
	flag[self] = 1;
	turn = 1-self;

	while ( flag[ 1 - self ] == 1 && turn == 1 - self );
}

void p_unlock(int self)
{
	flag[self] = 0;
}


/* Calculate the summation in two threads. */
void * calculate(void * arg)
{
	long countdown = BIG_NUM;

#ifdef _D
	int self  = *(int*) arg;
	int other = 1 - self;
	d_lock(self, other);

#elif _P
	int self  = *(int*) arg;
	p_lock(self);

#elif _PTHREAD
	pthread_mutex_lock(&mutex);

#endif

	while( countdown > 0 ) {
	/* Critical section */
		countdown--;
		global_value++;
	}

#ifdef _D
	d_unlock(self, other);
#elif _P
	p_unlock(self);
#elif _PTHREAD
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

#ifdef _D
	d_lock_init();
#elif _P
	p_lock_init();
#elif _PTHREAD
	pthread_mutex_init(&mutex, NULL);
#endif

	pthread_t thread[2];

	input_1 = (int *) malloc( sizeof(int) );
	input_2 = (int *) malloc( sizeof(int) );

	*input_1 = 0;
	*input_2 = 1;

        clock_gettime(CLOCK_REALTIME, &start);

	pthread_create(&thread[0], NULL, &calculate, (void *) input_1);
	pthread_create(&thread[1], NULL, &calculate, (void *) input_2);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);

	clock_gettime(CLOCK_REALTIME, &end);

	printf("\tExcepted global value: %d\t", BIG_NUM + BIG_NUM);
	printf("Calculated global value: %lu\t", global_value);

        time_diff = time_diff_in_second(start, end);
        printf("Time difference in sencond: %lf\n", time_diff);

	return 0;
}
