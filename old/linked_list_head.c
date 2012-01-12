/*
 * Linked list operations implementation 
 */

#include "../mds/mds_errors.h"
#include "linked_list_head.h"

void ll_insert(struct linked_list *l, struct generic_data d, int pos)
{
	if(pos<=0)
		mds_error(1, "Cannot insert element at negative index");
	if(pos>l->size+1)
		mds_error(1, "Insert new element with out of range index");

	struct node *ins = malloc(sizeof *ins);
	ins->next = l->head.next;
	if(pos==1) {
		if(l->is_set) {
			ins->data = l->head.data;
			l->head.data = d;
			l->head.next = ins;
		} else {
			l->head.data = d;
			l->is_set = 1;
		}
	} else {
		struct node *prev =& l->head;
		//go back 2 positions: 
		//	1) head is a node with value which we don't count in the loop, 
		//	2) the main reason for the loop is prev (one pos behind)
		pos-=2;
		while(pos--) {
			prev = ins->next;
			ins->next = ins->next->next;
		}
		prev->next = ins;
		ins->data = d;
	}
	l->size++;
}			

struct generic_data ll_remove(struct linked_list *l, int pos)
{
	if(pos<=0)
		mds_error(1, "Cannot remove element with negative index");
	if(pos>l->size)
		mds_error(1, "Remove new element with out of range index");
	
	struct node *rm;
	struct generic_data data;
	if(pos==1) {
		rm = l->head.next;
		data = l->head.data;
		l->head.data = rm->data;
		l->head.next = rm->next;
		free(rm);
	} else {
		rm =& l->head;
		struct node *prev;
		while(pos--) {
			prev = rm;
			rm = rm->next;
		}
		data = rm->data;
		prev->next = rm->next;
		free(rm);
	}
	l->size--;
	if(l->size==0)
		l->is_set = 0;
	return data;
}

struct linked_list* ll_init()
{
	struct linked_list *ll = malloc(sizeof *ll);	
	ll->head.next = NULL;
	ll->size = 0;
	ll->is_set = 0;
	return ll;
}

void ll_walk(struct linked_list *l, void (*f)(struct generic_data))
{
	if(l->size>0) {
		struct node *it =& l->head;
		while(it!=NULL) {
			f(it->data);
			it = it->next;
		}
	}
}
