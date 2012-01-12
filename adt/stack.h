/*
 * Stack implementation using a singly linked list
 * Push/pop/peek operations run in O(1) time
 * 
 * For underflow/overflow cases, an error message is printed
 * 
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "../bds/linked_list.h"

#define STACK_MAX_CAPACITY		128

#define STACK_OP_PUSH			(1<<0)
#define STACK_OP_POP			(1<<1)
#define STACK_OP_PEEK			(1<<2)

typedef struct {
	struct linked_list *list;
	uchar_t flags;
	uchar_t last_op;
} stack_t;

/* Returns a newly initialized stack */
stack_t* s_init();
/* Pushes a new element onto the stack */
void s_push(stack_t *s, struct generic_data data);
/* Returns the element at the top of the stack and removes it */
struct generic_data s_pop(stack_t *s);
/* Returns the element at the top of the stack, but does not remove it */
struct generic_data s_peek(stack_t *s);
/* Returns the number of elements in the stack */
size_t s_size(stack_t *s);
/* Returns 0 if the stack is empty, 1 otherwise */
uchar_t s_isEmpty(stack_t *s);
/* Prints the elements in a stack, with the element at the top first */
void s_print(stack_t *s);

#endif
