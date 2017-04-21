/* list.h
 * This header includes two kinds of list: array list and linked list.
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "generic.h"

/* typedef */
typedef struct list_operation list_operation_t;

typedef struct array_list array_list_t;
typedef struct linked_list linked_list_t;
typedef struct node node_t;


/* A structure includes all operations of array list or linked list */
struct list_operation {
	void (* push) (struct list_operation * list, int value);
	void * (* pop) (struct list_operation * list);
	int (* is_empty) (struct list_operation * list);
};


/* array list */
struct array_list {
	int * data;
	size_t used_size;
	size_t capacity;
	struct list_operation list_op;
};


/* linked list node and list */
struct node {
	int value;
	struct node * next;
};

struct linked_list {
	struct node * head;
	struct list_operation list_op;
};

/* function
 * Only shows the functions which are creation or deletion of array list and linked list,
 * the really operations are encapsulated in the individual operations structures.
 */

 /* array list */
extern array_list_t * array_list_create(size_t _capacity);
extern void array_list_delete(array_list_t * array_list);

/* linked list node and list */
extern linked_list_t * linked_list_create();
extern void linked_list_delete(linked_list_t * linked_list);

#endif
