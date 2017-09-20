# Object Oriented Programming Linked list

## Introduction

we implement a linked list under the concepts of object-oriented in C language.
Furthermore, extend the original template to different variants.
It includes the concepts of encapsulation, inheritance, and polymorphism.

## Basic Structure

Structure of array list and linked list:
```c
struct list_operation {
	void (* push) (struct list_operation * list_op, int value);
	void * (* pop) (struct list_operation * list_op);
	int (* is_empty) (struct list_operation * list_op);
};
```

Structure of linked queue and blocking queue:
```c
struct queue_operation{
	void (* add)(struct queue_operation * queue_op, int value);
	void * (* remove)(struct queue_operation * queue_op);
	int (* is_empty)(struct queue_operation * queue_op);
};
```

## Operations

Operations of array list and linked list:
```c
void (* push) (struct list_operation * list_op, int value);
void * (* pop) (struct list_operation * list_op);
int (* is_empty) (struct list_operation * list_op);
```

Operations of linked queue and blocking queue:
```c
void (* add)(struct queue_operation * queue_op, int value);
void * (* remove)(struct queue_operation * queue_op);
int (* is_empty)(struct queue_operation * queue_op);
```

## Individual functions

### Array list

```c
/* Array list */
extern array_list_t * array_list_create(size_t _capacity);
extern void array_list_delete(array_list_t * array_list);
```

### Linked list

```c
/* Linked list node and list */
extern linked_list_t * linked_list_create();
extern void linked_list_delete(linked_list_t * linked_list);
```
### Linked queue

```c
extern linked_queue_t * linked_queue_operation_create(struct list_operation * list_op);
extern linked_queue_t * linked_queue_create();
extern void linked_queue_delete_queue(linked_queue_t * queue);
extern void linked_queue_delete(linked_queue_t * queue);
```

### Blocking queue

```c
extern blocking_queue_t * blocking_queue_operation_create(struct queue_operation * queue);
extern blocking_queue_t * blocking_queue_create();
extern void blocking_queue_delete_queue(blocking_queue_t * queue);
extern void blocking_queue_delete(blocking_queue_t * queue);
```

## How to run

USAGE:
> gcc -Wall main.c array_list.c linked_list.c linked_queue.c blocking_queue.c && ./a.out

MEMORY TEST or DEBUG:
> gcc -Wall -g main.c array_list.c linked_list.c linked_queue.c blocking_queue.c && valgrind -v ./a.out
> gcc -Wall -g main.c array_list.c linked_list.c linked_queue.c blocking_queue.c && gdbtui ./a.out

GPROF:
> gcc -Wall -pg -g main.c array_list.c linked_list.c linked_queue.c blocking_queue.c && ./a.out && gprof -b ./a.out

PERF:
> gcc -Wall -g main.c array_list.c linked_list.c linked_queue.c blocking_queue.c && sudo perf record ./a.out
> sudo perf report

```bash
Samples: 15  of event 'cycles:pp', Event count (approx.): 21524669
Overhead  Command  Shared Object      Symbol                       
  80.86%  a.out    a.out              [.] linked_list_push         
  10.46%  a.out    [kernel.kallsyms]  [k] __alloc_pages_nodemask   
   7.86%  a.out    a.out              [.] blocking_queue_remove    
   0.79%  a.out    [kernel.kallsyms]  [k] get_random_int           
   0.03%  perf     [kernel.kallsyms]  [k] native_write_msr_safe    
```
The most of operations is extend from the function: linked_list_push().

## References:
 - Objekt-orientierte Programmierung mit ANSI-C 1994, Hanser, München, ISBN 3-446-17426-5.
 - [Can you write object-oriented code in C?](https://stackoverflow.com/questions/351733/can-you-write-object-oriented-code-in-c)
 - [Object-oriented programming Wiki](https://en.wikipedia.org/wiki/Object-oriented_programming)
 - [QMonkey/Object-Oriented-C](https://github.com/QMonkey/Object-Oriented-C)
