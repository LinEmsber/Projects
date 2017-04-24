#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "generic.h"
#include "list.h"
#include "queue.h"

static void blocking_queue_add(queue_operation_t * queue, int value);
static node_t * blocking_queue_remove(queue_operation_t * queue);
static int blocking_queue_is_empty(queue_operation_t * queue);

blocking_queue_t * blocking_queue_operation_create(queue_operation_t * _queue_op)
{
	blocking_queue_t * bq = malloc( sizeof(*bq) );
	if(bq == NULL)
		return NULL;

	bq->queue_op = _queue_op;

	int err = pthread_mutex_init(&bq->mutex, NULL);
	if(err)	{
		perror(strerror(err));
		exit(1);
	}

	err = pthread_cond_init(&bq->cond, NULL);
	if(err)	{
		perror(strerror(err));
		exit(1);
	}

	bq->blocking_queue_op.add = blocking_queue_add;
	bq->blocking_queue_op.remove = (void *)blocking_queue_remove;
	bq->blocking_queue_op.is_empty = blocking_queue_is_empty;

	return bq;
}

blocking_queue_t * blocking_queue_create()
{
	linked_queue_t * lq = linked_queue_create();
	if(lq == NULL)
		return NULL;

	return blocking_queue_operation_create(&lq->queue_op);
}

void blocking_queue_delete_queue(blocking_queue_t * _bq)
{
	int err = pthread_cond_destroy(&_bq->cond);
	if(err){
		perror(strerror(err));
	}

	err = pthread_mutex_destroy(&_bq->mutex);
	if(err){
		perror(strerror(err));
	}

	free(_bq);
}

void blocking_queue_delete(blocking_queue_t * _bq)
{
	linked_queue_t * lq = container_of(_bq->queue_op, linked_queue_t, queue_op);
	linked_queue_delete(lq);
	blocking_queue_delete_queue(_bq);
}


/* operation */
void blocking_queue_add(queue_operation_t * _bq_op, int value)
{
	blocking_queue_t * bq = container_of(_bq_op, blocking_queue_t, blocking_queue_op);

	int err = pthread_mutex_lock(&bq->mutex);
	if(err)
		perror(strerror(err));

	bq->queue_op->add(bq->queue_op, value);

	err = pthread_mutex_unlock(&bq->mutex);
	if(err)
		perror(strerror(err));

	err = pthread_cond_signal(&bq->cond);
	if(err)
		perror(strerror(err));
}

node_t * blocking_queue_remove(queue_operation_t * _bq_op)
{
	blocking_queue_t * bq = container_of(_bq_op, blocking_queue_t, blocking_queue_op);
	int err = pthread_mutex_lock(&bq->mutex);
	if(err)
		perror(strerror(err));

	while( bq->blocking_queue_op.is_empty( &bq->blocking_queue_op ) ) {
		err = pthread_cond_wait(&bq->cond, &bq->mutex);
		if(err)
			perror(strerror(err));
	}

	node_t * n = bq->queue_op->remove(bq->queue_op);

	err = pthread_mutex_unlock(&bq->mutex);
	if(err)
		perror(strerror(err));

	return n;
}

int blocking_queue_is_empty(queue_operation_t * _bq_op)
{
	blocking_queue_t * bq = container_of(_bq_op, blocking_queue_t, blocking_queue_op);

	return bq->queue_op->is_empty(bq->queue_op);
}
