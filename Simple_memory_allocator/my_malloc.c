
# include <stdio.h>
# include <string.h>
# include <unistd.h>

#include "my_malloc.h"

/* A global pointer points to the first allocate node.
 * We can traversal this node to find the target node.
 */
list_t * g_list;

void * my_malloc(size_t size)
{
	void * addr;
	static int i = 0;

	if (size == 0)
		return NULL;

	/* memory align
	 * TODO: use a better method.
	 */
	size = (size - 1) / 4 * 4 + 4;
	addr = find_block(size);

	if (addr != NULL) {
		re_init_list();
		return addr;
	}

	/* After sbrk(), we support addr is (void *) 0x603000. */
	addr = sbrk(size);
	if (addr == (void *) -1) {
		printf("Error : sbrk() failed\n");
		return NULL;
	}

	if (i == 0)
		g_list = NULL;

	put_in_list(&g_list, size, addr);
	++i;

	return addr;
}

void * find_block(size_t size)
{
	/* The global list is not initialize yet. */
	if (g_list == NULL)
		return NULL;

        /* Check the state of the last operated node, g_list. */
	if (g_list->is_used == UNUSED && size <= g_list->size) {
		g_list->is_used = USED;
		return g_list->addr;
	}

	/* Find the unused block for this request.
         * In here, we use the first fit algortihm to search the unused node.
         */
	while(g_list->head != 1) {
		if (g_list->is_used == UNUSED && size <= g_list->size) {
			g_list->is_used = USED;
			return g_list->addr;
		}
		g_list = g_list->next;
	}

	/* If we cannot find any unused node, reset the pointer, g_list. */
	re_init_list();

	return NULL;
}

void * my_realloc(void * ptr, size_t size)
{
	void * cpy;
	size_t ptr_size;

	if (size == 0 && ptr != NULL) {
		my_free(ptr);
		return ptr;
	}
	else if (ptr == NULL || is_in_list(ptr) == 1){
		ptr = my_malloc(size);

	} else {
		ptr_size = get_size(ptr);
		if (ptr_size == size)
			return ptr;

		cpy = my_malloc(size);

		if (size < ptr_size)
			memcpy(cpy, ptr, size);
		else
			memcpy(cpy, ptr, ptr_size);

		my_free(ptr);
		return cpy;
	}

	return ptr;
}

int is_in_list(void * ptr)
{
	list_t * tmp;

	tmp = g_list;
	while (tmp->addr != ptr && tmp->head != 1)
		tmp = tmp->next;

	if (tmp->addr != ptr)
		return 1;

	return 0;
}

size_t get_size(void * ptr)
{
	list_t * tmp;

	tmp = g_list;
	while (tmp->addr != ptr)
		tmp = tmp->next;
	return (tmp->size);
}

void my_free(void * ptr)
{
	if (ptr == NULL)
		return ;

	if (is_in_list(ptr) == 1)
		return ;

	while (ptr != g_list->addr && g_list->head != 1)
		g_list = g_list->next;

	if (g_list->is_used == UNUSED)
		return ;

	g_list->is_used = UNUSED;
	if (g_list->head != 1) {
		if (g_list->next->is_used == UNUSED && g_list->next->addr != g_list->addr) {
			if (g_list->addr > g_list->next->addr) {
				g_list->addr = g_list->next->addr;
			}

			g_list->head = g_list->next->head;
			g_list->size += g_list->next->size;
			g_list->next = g_list->next->next;
		}
	}
	re_init_list();
}

void put_in_list(list_t ** list, size_t size, void * addr)
{
	list_t * tmp;

	/* allocate memroy for tmp
	 * before allocate memory for this tmp, this pointer point to random number.
	 * After sbrk(), we support addr is (void *) 0x603040. 0x603040 = 0x603000 + 0x40, we allocate 40 byte in this time.
	 */
	tmp = sbrk( sizeof(*tmp) );
	if (tmp == (void *)-1) {
		printf("Error : sbrk() failed\n");
		return ;
	}

	tmp->size = size;
	tmp->is_used = USED;
	/* After sbrk(), we support addr is (void *) 0x603000. */
	/* After assignment, tmp->addr is 0x603000. */
	tmp->addr = addr;

	/* If *list is NULL, it means this tmp is the first node of the linked list.
	 * We set it as the head.
	 */
	if (*list == NULL){
		tmp->head = 1;

	} else {
		tmp->head = 0;
		tmp->next = *list;
		if (tmp->next)
			tmp->next->prev = tmp;
	}

	*list = tmp;
	make_circle(list);
}

/* Make this list as the circular linked list. */
void make_circle(list_t ** list)
{
        /* The variable, tmp, store the pointer of the input node, *list.
         * We use *list to represent the head, and restore it back to original input list in the last step.
         */
	list_t * tmp;
	tmp = *list;

	/* Find the head of the list. */
	while ((*list)->head != 1)
		(*list) = (*list)->next;

        /* The next node of the head is tmp. The prev of tmp is the head. */
	(*list)->next = tmp;
	(*list)->next->prev = *list;

        /* Restore *list as the pointer of tmp. */
	while ((*list) != tmp)
		*list = (*list)->next;
}

/* Set the first actually allocated node as the g_list. */
void re_init_list()
{
        /* Find the head, and the next node of the head is the first actually allocated node. */
	while (g_list->head != 1)
		g_list = g_list->next;

	g_list = g_list->next;
}

int main()
{
	int * p_1 = my_malloc( sizeof(int) * 4 );
	int * p_2 = my_malloc( sizeof(int) * 10 );
	int * p_3 = my_malloc( sizeof(char) * 25 );
        int * p_4 = my_malloc( sizeof(int) * 10 );
        int * p_5 = my_malloc( sizeof(int) * 10 );

	// my_free(p_1);
	// my_free(p_2);
	// my_free(p_3);

	return 0;
}
