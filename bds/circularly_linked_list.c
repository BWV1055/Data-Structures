/*
 * Circularly linked list methods 
 */

#include "../mds/mds_errors.h"
#include "circularly_linked_list.h"

void cll_insert(struct circularly_linked_list *l, struct generic_data d, int pos)
{
	if(pos<=0)
		mds_error(1, "Cannot insert element at negative index");
	if(pos>l->size+1)
		mds_error(1, "Insert new element with out of range index");

	struct node *ins = malloc(sizeof *ins);
	if(pos==1)
		l->cur = ins->next = ins;
	else {
		struct node *prev;
		//we are interested in prev, which should be one position behind pos
		pos--;
		while(pos--) {
			prev = ins->next;
			ins->next = ins->next->next;
		}
		prev->next = ins;
	}
	ins->data = d;
	l->size++;
}			

struct generic_data ll_remove(struct linked_list *l, int pos)
{
	if(ll_isEmpty(l))
		mds_error(1, "Linked list is empty");
	if(pos<=0)
		mds_error(1, "Cannot remove element with negative index");
	if(pos>l->size)
		mds_error(1, "Remove new element with out of range index");
	
	struct node *rm = l->head;
	struct generic_data data;
	if(pos==1) {
		l->head = rm->next;
	} else {
		struct node *prev;
		while(pos--) {
			prev = rm;
			rm = rm->next;
		}
		prev->next = rm->next;
	}
	data = rm->data;
	free(rm);
	l->size--;
	return data;
}

int ll_size(struct linked_list *l)
{
	return l->size;
}

int ll_isEmpty(struct linked_list *l)
{
	return (ll_size(l)==0);
}

struct circularly_linked_list* cll_init()
{
	struct circularly_linked_list *l = malloc(sizeof *l);	
	l->cur = NULL;
	l->size = 0;
	return l;
}

void ll_walk(struct linked_list *l, void (*f)(struct generic_data))
{
	if(l->size>0) {
		struct node *it = l->head;
		while(it!=NULL) {
			f(it->data);
			it = it->next;
		}
	}
}
