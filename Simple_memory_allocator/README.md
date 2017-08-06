# Simple memory allocator

## Introduction

Use Linux system call brk() and sbrk() to make a simple memory allocator.

## Concept

### Structure
```c
struct list_s{
	size_t size;
	int is_used;
	void * addr;
	int head;
	struct list_s * prev;
	struct list_s * next;
};
```

### Function

```c
void * my_malloc(size_t size);

void * find_block(size_t size);

void * my_realloc(void * ptr, size_t size);

int is_in_list(void * ptr);

size_t get_size(void * ptr);

void my_free(void * ptr);

void put_in_list(list_t ** list, size_t size, void * addr);

void make_circle(list_t ** list);

void re_init_list();
```

## References
[malloc-free-realloc-using-brk-and-sbrk](https://codereview.stackexchange.com/questions/80190/malloc-free-realloc-using-brk-and-sbrk)
