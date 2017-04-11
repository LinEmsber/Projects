#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "list.h"

/* declaration of function */
static void array_list_push(list_operation_t * l_op, int value);
static int array_list_pop(list_operation_t * l_op);
static int array_list_is_empty(list_operation_t * l_op);

static void array_list_resize(array_list_t *al, size_t size);


/* create and delete array list */
array_list_t * array_list_create(size_t size)
{
	if(size <= 0)
		size = 1;

	array_list_t * al = (array_list_t*) malloc( sizeof(array_list_t) );
	if(al  == NULL)
		return NULL;

	al->capacity = 0;
	al->size = size;

	al->data = (int*) malloc( sizeof(int) * size );

	al->list_op.push = array_list_push;
	al->list_op.pop = array_list_pop;
	al->list_op.is_empty = array_list_is_empty;

	return al;
}

void array_list_delete(array_list_t * al)
{
	free(al->data);
	free(al);
}


/* operations of array list */
void array_list_push(list_operation_t *l_op, int elem)
{
	array_list_t * al = container_of(l_op, array_list_t, list_op);

	if(al->capacity == al->size)
		array_list_resize(al, al->size << 1);

	al->data[al->capacity] = elem;
        al->capacity++;
}

int array_list_pop(list_operation_t *l_op)
{
	array_list_t * al = container_of(l_op, array_list_t, list_op);
        --al->capacity;

	return al->data[al->capacity];
}

int array_list_is_empty(list_operation_t *l_op)
{
	array_list_t * al = container_of(l_op, array_list_t, list_op);

	return al->capacity == 0;
}

void array_list_resize(array_list_t * al, size_t size)
{
	if(size <= al->size)
		return ;

	int * data = (int*) malloc( sizeof(int) * size );

	memcpy(data, al->data, al->size * sizeof(int));
	free(al->data);

	al->data = data;
	al->size = size;
}
