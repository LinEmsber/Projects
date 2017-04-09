#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "generic.h"
#include "list.h"

static void linked_list_push(list_operation_t * list_op, int value);
static int linked_list_pop(list_operation_t * list_op);
static int linked_list_empty(list_operation_t * list_op);

/* create and delete linked list */
linked_list_t * linked_list_create()
{
	linked_list_t * ll = (linked_list_t *) malloc( sizeof(linked_list_t) );
	if(ll == NULL)
		return NULL;

	ll->head = NULL;
	ll->list_op.push = linked_list_push;
	ll->list_op.pop = linked_list_pop;
	ll->list_op.empty = linked_list_empty;

	return ll;
}

void linked_list_delete(linked_list_t * ll)
{
	list_node_t * tmp = ll->head;

	while(ll->head != NULL){
		ll->head = tmp->next;
		free(tmp);
	}

	free(ll);
}


/* operations of linked list */
void linked_list_push(list_operation_t * list_op, int value)
{
        linked_list_t * ll = container_of(list_op, linked_list_t, list_op);

	list_node_t ** node = &ll->head;
	while(*node != NULL) {
		node = &(*node)->next;
	}

	list_node_t * n = (list_node_t *) malloc( sizeof(list_node_t) );
	n->value = value;
	n->next = NULL;

	*node = n;
}

int linked_list_pop(list_operation_t * list_op)
{
        linked_list_t * ll = container_of(list_op, linked_list_t, list_op);
	assert(ll->head != NULL);

	list_node_t * tmp = ll->head;
	ll->head = tmp->next;

	int value = tmp->value;
	free(tmp);

	return value;
}

int linked_list_empty(list_operation_t * list_op)
{
        linked_list_t * ll = container_of(list_op, linked_list_t, list_op);
	return ll->head == NULL;
}
