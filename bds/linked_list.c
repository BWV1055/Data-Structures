/*
 *
 *
 */

#include "linked_list.h"

void insert_node(struct linked_list list, struct generic_data d, uint pos)
{
	if(pos<=0)
	{ /*error*/ }
	if(pos>list.total+1)
	{ /*error*/ }

	node *to_insert = (node*)malloc(sizeof(node));
	node *prev = (node*)malloc(sizeof(node));
	to_insert->data = d;

	to_insert->next = list.head;
	prev = list.head;
	while(pos--)
	{
		prev = to_insert->next;
		to_insert->next = to_insert->next->next;
	}
	prev = to_insert;
}
	
struct linked_list* ll_init() {
	struct linked_list* new = malloc(sizeof(*new));
	new->total = 0;
	new->head = NULL;
	return new;
}	

