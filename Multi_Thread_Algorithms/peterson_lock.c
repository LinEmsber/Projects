/* The Paterson's algorithm.
 *
 * gcc -Wall -pthread peterson_lock.c && ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int flag[2];
int turn;
const int MAX = 50;
int counter = 0;

/* Init flags for two locks. */
void lock_init()
{
	flag[0] = flag[1] = 0;
	turn = 0;
}

void lock(int self)
{
	flag[self] = 1;
	turn = 1 - self;

	/* Wait until the other thread looses the desire to acquire lock,
	 * or it is your turn to get the lock.
	 */
	while ( flag[ 1 - self ] == 1 && turn == 1 - self );
}

void unlock(int self)
{
	/* allow the other thread to acquire the lock. */
	flag[self] = 0;
}

void * test_function(void *s)
{
	int i = 0;
	int self = *(int *)s;

	printf("Thread Entered: %d\n", self);

	lock(self);

	/* critical section */
	for ( i = 0; i < MAX; i++ )
		counter++;

	unlock(self);

	return 0;
}

int main()
{
	pthread_t p1, p2;
	int *one = malloc(sizeof(int));
	int *zero = malloc(sizeof(int));

	*zero = 0;
	*one = 1;

	lock_init();

	pthread_create( &p1, NULL, test_function, (void*)zero );
	pthread_create( &p2, NULL, test_function, (void*)one );

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	printf("Actual Count: %d\n", counter);
	printf("Expectd Count: %d\n", MAX * 2);

	return 0;
}
