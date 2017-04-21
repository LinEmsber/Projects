#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "list.h"

/* declaration of function */
static void array_list_push(list_operation_t * l_op, int value);
static int * array_list_pop(list_operation_t * l_op);
static int array_list_is_empty(list_operation_t * l_op);

static void array_list_resize(array_list_t *al, size_t capacity);


/* create and delete array list */
array_list_t * array_list_create(size_t _capacity)
{
	if(_capacity <= 0)
		_capacity = 1;

	array_list_t * al = malloc( sizeof(* al) );
	if(al  == NULL)
		return NULL;

	al->used_size = 0;
	al->capacity = _capacity;

	al->data = (int*) malloc( sizeof(int) * _capacity );

	al->list_op.push = array_list_push;
	al->list_op.pop = (void * ) array_list_pop;
	al->list_op.is_empty = array_list_is_empty;

	return al;
}

void array_list_delete(array_list_t * _al)
{
	free(_al->data);
	free(_al);
}


/* operations of array list */
void array_list_push(list_operation_t * _al_op, int _value)
{
	array_list_t * al = container_of(_al_op, array_list_t, list_op);

	/* If the used_size of array list is full, create double capacity for it. */
	if(al->used_size == al->capacity)
		array_list_resize(al, al->capacity << 1);

	al->data[al->used_size] = _value;
        al->used_size++;
}

int * array_list_pop(list_operation_t * _al_op)
{
	array_list_t * al = container_of(_al_op, array_list_t, list_op);
        al->used_size--;

	int * p = malloc(sizeof(int));
	p = &al->data[al->used_size];

	return p;
}

int array_list_is_empty(list_operation_t * _al_op)
{
	array_list_t * al = container_of(_al_op, array_list_t, list_op);

	return al->used_size == 0;
}

void array_list_resize(array_list_t * _al, size_t _size)
{
	if(_size <= _al->capacity)
		return ;

	int * data = (int*) malloc( sizeof(int) * _size );

	memcpy(data, _al->data, _al->capacity * sizeof(int));
	free(_al->data);

	_al->data = data;
	_al->capacity = _size;
}
