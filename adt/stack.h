/*
 * Stack implementation using a singly linked list
 * Push and pop operations run in O(1) time
 * 
 * For underflow/overflow cases, an error message is returned
 * 
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "../bds/linked_list.h"

#define STACK_MAX_CAPACITY		128

#define STACK_OP_PUSH			(1<<0)
#define STACK_OP_POP			(1<<1)
#define STACK_OP_PEEK			(1<<2)

struct stack {
	struct linked_list list;
	uchar flags;
	uchar last_op;
};

/* Returns a newly initialized stack */
struct stack* s_init();
/* Pushes a new element onto the stack */
void s_push(struct stack *s, struct generic_data data);
/* Returns the element at the top of the stack and removes it */
struct generic_data s_pop(struct stack *s);
/* Returns the element at the top of the stack, but does not remove it 
 * This operation allows both to examine the top of the stack, and to
 * change the value (which would otherwise require a push/pop) */
struct generic_data* s_peek(struct stack *s);
/* Returns the number of elements in the stack */
size_t s_size(struct stack *s);
/* Returns 0 if the stack is empty, 1 otherwise */
uchar s_isEmpty(struct stack *s);

#endif
