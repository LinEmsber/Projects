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
	linked_list_t * linked_list_entry = linked_list_create();

	for(i = 0; i < LOOP_NUMS; ++i)
	{
		linked_list_entry->list_op.push(&linked_list_entry->list_op, i);
	}

	for(i = 0; i < LOOP_NUMS; ++i)
	{
		printf("%d ", linked_list_entry->list_op.pop(&linked_list_entry->list_op));
	}
	printf("empty: %d\n", linked_list_entry->list_op.empty(&linked_list_entry->list_op));
	printf("\n");

	linked_list_delete(linked_list_entry);

	return 0;
}
