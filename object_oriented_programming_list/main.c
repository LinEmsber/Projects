/* main.c
 *
 * USAGE: gcc -Wall -g main.c linked_list.c array_list.c && ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "list.h"

#define LOOP_NUMS 10

int main()
{
        int i;
        void * tmp_n;

        /* array list */
        array_list_t * array_list_entry = array_list_create(0);

	for(i = 0; i < LOOP_NUMS; ++i)
		array_list_entry->list_op.push(&array_list_entry->list_op, i);

	for(i = 0; i < LOOP_NUMS; ++i){
                tmp_n = array_list_entry->list_op.pop(&array_list_entry->list_op);
                printf("tmp_n->value: %d\n", *(int *) tmp_n);
        }

	printf("is_empty: %d\n", array_list_entry->list_op.is_empty(&array_list_entry->list_op));

	array_list_delete(array_list_entry);

        /* linked list */
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

	return 0;
}
