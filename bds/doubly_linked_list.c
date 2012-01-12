/*
 * Doubly linked list operations implementation
 * TO DO: implement a function to walk the list to pos node
 *        use this function in both dll_insert and dll_remove
 *
 */

#include "doubly_linked_list.h"

void dll_insert(struct doubly_linked_list *dll, struct generic_data data, int pos)
{
	if(pos<=0)
		mds_error(1, "Cannot insert element at negative index");
	if(pos>dll->size+1)
		mds_error(1, "Insert new element with out of range index");

	struct node *ins = malloc(sizeof *ins);
	ins->next = dll->head->next;

	if(pos==1)
		ins->prev = dll->head;
	else {
		//have to do this because head is also a node, but we don't consider it
		pos--;
		while(pos--)
			ins->next = ins->next->next;
		ins->prev = ins->next->prev;
	}

	ins->prev->next = ins;
	ins->next->prev = ins;
	ins->data = data;
	dll->size++;
}

struct generic_data dll_remove(struct doubly_linked_list *dll, int pos)
{
	if(!dll->size)
		mds_error(1, "Cannot remove from empty list");
	if(pos<=0)
		mds_error(1, "Cannot remove element at negative index");
	if(pos>dll->size+1)
		mds_error(1, "Not enough elements");

	struct node *it = dll->head;
	struct generic_data data;
	while(pos--)
		it = it->next;
	it->prev->next = it->next;
	it->next->prev = it->prev;
	data = it->data;
	free(it);
	dll->size--;
	return data;
}

void dll_walk(struct doubly_linked_list *dll, void (*f)(struct generic_data))
{
	if(dll->size) {
		struct node *it = dll->head->next;
		do{
			f(it->data);
			it = it->next;
		}while(it!=dll->head);
	}
}

struct doubly_linked_list* dll_init()
{
	struct doubly_linked_list *init = malloc(sizeof *init);
	init->size = 0;
	init->head = malloc(sizeof *(init->head));
	init->head->next = init->head->prev = init->head;
	return init;
}

/* Visiting function examples */

void dll_compare_value(struct generic_data data) {
	/* The function calling dll_compare_value should also declare these two as extern 
	 * So they can be used as a way of transmitting data */
	extern key_t tempKey;
	extern pos;
	if(data.key>tempKey)
		pos = 1;
}
