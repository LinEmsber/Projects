
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "list.h"
#include "queue.h"

#define LOOP_NUMS 100

int main()
{
        int i;
        void * tmp_n;


        /* Linked list. */
	linked_list_t * linked_list_entry = linked_list_create();

	for(i = 0; i < LOOP_NUMS; ++i)
		linked_list_entry->list_op.push(&linked_list_entry->list_op, i);

	for(i = 0; i < LOOP_NUMS; ++i){
                tmp_n = linked_list_entry->list_op.pop(&linked_list_entry->list_op);
                printf("tmp_n->value: %d\n", ( (node_t *) tmp_n )->value);
                free(tmp_n);
        }

	printf("is_empty: %d\n", linked_list_entry->list_op.is_empty(&linked_list_entry->list_op));

	linked_list_delete(linked_list_entry);


        /* Array list. */
        array_list_t * array_list_entry = array_list_create(0);

        for(i = 0; i < LOOP_NUMS; ++i)
        array_list_entry->list_op.push(&array_list_entry->list_op, i);

        for(i = 0; i < LOOP_NUMS; ++i){
                tmp_n = array_list_entry->list_op.pop(&array_list_entry->list_op);
                printf("tmp_n->value: %d, address: %p\n", *(int *) tmp_n, tmp_n);
        }

        printf("is_empty: %d\n", array_list_entry->list_op.is_empty(&array_list_entry->list_op));

        array_list_delete(array_list_entry);


        /* Queue. */
        linked_queue_t * linked_queue_entry = linked_queue_create();
        printf("linked_queue_is_empty(linked_queue_entry): %d\n", linked_queue_entry->queue_op.is_empty(&linked_queue_entry->queue_op));

        for(i = 0; i < LOOP_NUMS; ++i)
		linked_queue_entry->queue_op.add(&linked_queue_entry->queue_op, i);

        printf("linked_queue_is_empty(linked_queue_entry): %d\n", linked_queue_entry->queue_op.is_empty(&linked_queue_entry->queue_op));

	for(i = 0; i < LOOP_NUMS; ++i){
                tmp_n = linked_queue_entry->queue_op.remove(&linked_queue_entry->queue_op);
                printf("tmp_n->value: %d\n", ( (node_t *) tmp_n )->value);
                free(tmp_n);
        }

        linked_queue_delete(linked_queue_entry);


        /* Blocking queue. */
        blocking_queue_t * blocking_queue_entry = blocking_queue_create();
        printf("blocking_queue_is_empty(blocking_queue_entry): %d\n", blocking_queue_entry->blocking_queue_op.is_empty(&blocking_queue_entry->blocking_queue_op));

        for(i = 0; i < LOOP_NUMS; ++i)
                blocking_queue_entry->blocking_queue_op.add(&blocking_queue_entry->blocking_queue_op, i);

        printf("blocking_queue_is_empty(blocking_queue_entry): %d\n", blocking_queue_entry->blocking_queue_op.is_empty(&blocking_queue_entry->blocking_queue_op));

        for(i = 0; i < LOOP_NUMS; ++i){
                tmp_n = blocking_queue_entry->blocking_queue_op.remove(&blocking_queue_entry->blocking_queue_op);
                printf("tmp_n->value: %d\n", ( (node_t *) tmp_n )->value);
                free(tmp_n);
        }

        blocking_queue_delete(blocking_queue_entry);

	return 0;
}
