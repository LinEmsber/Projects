/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "list.h"

#define LOOP_NUMS 10

int main()
{
        int i;

        /* array list */
        array_list_t * array_list_entry = array_list_create(0);

	for(i = 0; i < LOOP_NUMS; ++i)
		array_list_entry->list_op.push(&array_list_entry->list_op, i);

	for(i = 0; i < LOOP_NUMS; ++i)
		printf("%d ", array_list_entry->list_op.pop(&array_list_entry->list_op));

	printf("is_empty: %d\n", array_list_entry->list_op.is_empty(&array_list_entry->list_op));

	array_list_delete(array_list_entry);

        /* linked list */
	linked_list_t * linked_list_entry = linked_list_create();

	for(i = 0; i < LOOP_NUMS; ++i)
		linked_list_entry->list_op.push(&linked_list_entry->list_op, i);

	for(i = 0; i < LOOP_NUMS; ++i)
		printf("%d ", linked_list_entry->list_op.pop(&linked_list_entry->list_op));

	printf("is_empty: %d\n", linked_list_entry->list_op.is_empty(&linked_list_entry->list_op));

	linked_list_delete(linked_list_entry);

	return 0;
}
