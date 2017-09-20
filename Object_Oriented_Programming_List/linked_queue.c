#include <stdio.h>
#include <stdlib.h>

#include "generic.h"
#include "list.h"
#include "queue.h"

static void linked_queue_add(queue_operation_t * queue, int value);
static node_t * linked_queue_remove(queue_operation_t * queue);
static int linked_queue_is_empty(queue_operation_t * queue);

linked_queue_t * linked_queue_operation_create(list_operation_t * _list_op)
{
	linked_queue_t * lq = malloc( sizeof(*lq) );
	if(lq == NULL)
		return NULL;

	lq->list_op = _list_op;

	lq->queue_op.add = linked_queue_add;
	lq->queue_op.remove = (void *)linked_queue_remove;
	lq->queue_op.is_empty = linked_queue_is_empty;

	return lq;
}

linked_queue_t * linked_queue_create()
{
	linked_list_t * ll = linked_list_create();
	if(ll == NULL)
		return NULL;

	return linked_queue_operation_create(&ll->list_op);
}

void linked_queue_delete_queue(linked_queue_t * _lq)
{
	free(_lq);
}

void linked_queue_delete(linked_queue_t *_lq)
{
	linked_list_t * ll = container_of(_lq->list_op, linked_list_t, list_op);
	linked_list_delete(ll);
	linked_queue_delete_queue(_lq);
}


/* Operations of linked queue. */
void linked_queue_add(queue_operation_t * _lq_op, int _value)
{
	linked_queue_t * lq = container_of(_lq_op, linked_queue_t, queue_op);
	lq->list_op->push(lq->list_op, _value);
}

node_t * linked_queue_remove(queue_operation_t * _lq_op)
{
	linked_queue_t * lq = container_of(_lq_op, linked_queue_t, queue_op);
	return lq->list_op->pop(lq->list_op);
}

int linked_queue_is_empty(queue_operation_t * _lq_op)
{
	linked_queue_t * lq = container_of(_lq_op, linked_queue_t, queue_op);
	return lq->list_op->is_empty(lq->list_op);
}
