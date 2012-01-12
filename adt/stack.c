/*
 * Stack implementation using a singly linked list
 * Push and pop operations run in O(1) time
 * 
 * For underflow/overflow cases, an error message is returned
 * 
 */

#include "stack.h"

stack_t* s_init() {
	stack_t *ns = malloc(sizeof(*ns));
	ns->flags = 0;
	ns->last_op = 0;
	return ns;
}

/* Pushes a new element onto the stack */
void s_push(stack_t *s, struct generic_data data)
{
	if(ll_size(s->list)==STACK_MAX_CAPACITY) {
		mds_error(E_FULL_STACK, "Stack is full");
		return;
	}

	ll_insert_beginning(s->list, data);
}

struct generic_data s_pop(stack_t *s)
{
	if(ll_isEmpty(s->list)) {
		mds_error(E_EMPTY_STACK, "Stack is empty");
		return;
	}

	return ll_remove(s->list, 1);
}

struct generic_data s_peek(stack_t *s)
{
	if(ll_isEmpty(s->list)) {
		mds_error(E_EMPTY_STACK, "Stack is empty");
		return;
	}

	return ll_get(s->list, 1);
}	

size_t s_size(stack_t *s) {
	return s->list->total;
}

uchar_t s_isEmpty(stack_t *s) {
	return ll_isEmpty(s->list);
}

void s_print(stack_t *s) {
	printf("Stack elements (top first):\n");
	ll_walk(s->list, ll_print_elem);
}



/* Stack usage example 
 * This is an example for matching HTML tags in a document 
 * It reads file f and ... */

void match_HTML_tags(FILE *f) {
	




}
