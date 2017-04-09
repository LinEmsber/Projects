/* list.h */

#ifndef LIST_H
#define LIST_H

/* typedef */
typedef struct list_operation list_operation_t;
typedef struct array_list array_list_t;
typedef struct linked_list linked_list_t;
typedef struct list_node list_node_t;


/* A structure includes all operations of ArrayList or LinkedList */
list_operation_t {
	void (* push) (list_operation_t * list, int elem);
	int (* pop) (list_operation_t * list);
	int (* empty) (list_operation_t * list);
};


/* array list */
struct array_list {
	int * data;
	size_t capacity;
	size_t size;
	struct list_operation list_op;
};


/* linked list node and list */
struct list_node {
	int value;
	struct _ListNode * next;
};

struct _LinkedList {
	struct _ListNode * head;
	struct list_operation list_op;
};

/* function
 * Only shows the functions which are creation or deletion of array list and linked list,
 * the really operations are encapsulated in the individual operations structures.
 */

 /* array list */
extern array_list_t * array_list_create(size_t size);
extern void array_list_delete(array_list_t * array_list);

/* linked list node and list */
extern linked_list_t * linked_list_create();
extern void linked_list_delete(linked_list_t * linked_list);

#endif
