/* queue.h
 * This header includes two kinds of queue: linked queue and blocking queue.
 */


#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "list.h"
#include "generic.h"

/* typedef */
typedef struct queue_operation queue_operation_t;

typedef struct linked_queue linked_queue_t;

typedef struct blocking_queue blocking_queue_t;


/* structure */
struct queue_operation{
	void (* add)(struct queue_operation * queue_op, int value);
	void * (* remove)(struct queue_operation * queue_op);
	int (* is_empty)(struct queue_operation * queue_op);
};

struct linked_queue{
	struct list_operation * list_op;
	struct queue_operation queue_op;
};

struct blocking_queue
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	struct queue_operation * queue_op;
	struct queue_operation blocking_queue_op;
};

extern linked_queue_t * linked_queue_operation_create(struct list_operation * list_op);
extern linked_queue_t * linked_queue_create();
extern void linked_queue_delete_queue(linked_queue_t * queue);
extern void linked_queue_delete(linked_queue_t * queue);


extern blocking_queue_t * blocking_queue_operation_create(struct queue_operation * queue);
extern blocking_queue_t * blocking_queue_create();
extern void blocking_queue_delete_queue(blocking_queue_t * queue);
extern void blocking_queue_delete(blocking_queue_t * queue);

#endif
