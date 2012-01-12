/*
 *	Deque data structure and method definition
 *	The deque is implemented with a doubly linked list
 *
 */

#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "../bds/doubly_linked_list.h"

#define DEQUE_MAX_CAPACITY		256

#define DEQUE_OP_ADD_FIRST			(1<<0)
#define DEQUE_OP_ADD_LAST			(1<<1)
#define DEQUE_OP_REMOVE_FIRST		(1<<2)
#define DEQUE_OP_REMOVE_LAST		(1<<3)

typedef struct {
	struct doubly_linked_list *list;
	uchar_t flags;
	uchar_t last_op;
} deque_t;

/* Returns a newly initialized deque */
deque_t* dq_init();
/* Adds a new element at the front of the deque */
void dq_add_first(deque_t *q, struct generic_data data);
/* Adds a new element at the end of the deque */
void dq_add_last(deque_t *q, struct generic_data data);
/* Returns the element at the front of the deque and removes it */
struct generic_data dq_remove_first(deque_t *q);
/* Returns the element at the end of the deque and removes it */
struct generic_data dq_remove_last(deque_t *q);
/* Returns the element at the front of the deque, but does not remove it */
struct generic_data dq_get_first(deque_t *q);
/* Returns the element at the end of the deque, but does not remove it */
struct generic_data dq_get_last(deque_t *q);
/* Returns the number of elements in the deque */
size_t dq_size(deque_t *q);
/* Returns 0 if the deque is empty, 1 otherwise */
uchar_t dq_isEmpty(deque_t *q);
/* Prints the elements in a deque, with the element at the front first */
void dq_print(deque_t *q);

#endif
