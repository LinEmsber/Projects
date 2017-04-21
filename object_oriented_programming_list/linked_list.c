#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "generic.h"
#include "list.h"

/* declaration of function */
static void linked_list_push(list_operation_t * l_op, int value);
static node_t * linked_list_pop(list_operation_t * _ll_op);
static int linked_list_is_empty(list_operation_t * l_op);

/* create and delete linked list */
linked_list_t * linked_list_create()
{
	linked_list_t * ll = malloc( sizeof(* ll) );
	if(ll == NULL)
		return NULL;

	ll->head = NULL;
	ll->list_op.push = linked_list_push;
	ll->list_op.pop = (void * )linked_list_pop;
	ll->list_op.is_empty = linked_list_is_empty;

	return ll;
}

void linked_list_delete(linked_list_t * _ll)
{
	node_t * tmp = _ll->head;

	while(_ll->head != NULL){
		_ll->head = tmp->next;
		free(tmp);
	}

	free(_ll);
}


/* operations of linked list */
void linked_list_push(list_operation_t * _ll_op, int _value)
{
        linked_list_t * ll = container_of(_ll_op, linked_list_t, list_op);

	node_t ** node = &ll->head;
	while(*node != NULL) {
		node = &(*node)->next;
	}

	node_t * n = malloc( sizeof(* n) );
	n->value = _value;
	n->next = NULL;

	*node = n;
}

node_t * linked_list_pop(list_operation_t * _ll_op)
{
        linked_list_t * ll = container_of(_ll_op, linked_list_t, list_op);
	assert(ll->head != NULL);

	node_t * current = ll->head;
	ll->head = ll->head->next;

	current->next = NULL;

	return current;
}

int linked_list_is_empty(list_operation_t * _ll_op)
{
        linked_list_t * ll = container_of(_ll_op, linked_list_t, list_op);
	return ll->head == NULL;
}
