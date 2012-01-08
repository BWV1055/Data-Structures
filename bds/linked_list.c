/*
 *	Singly linked list operation implementation
 *
 */

#include "linked_list.h"

void ll_insert(struct linked_list *l, struct generic_data d, int pos)
{
	if(pos<=0)
		mds_error(1, "Cannot insert element at negative index");
	if(pos>l->size+1)
		mds_error(1, "Insert new element with out of range index");

	struct node *ins = malloc(sizeof *ins);
	ins->next = l->head;
	if(pos==1)
		l->head = ins;
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

int ll_insert_after(struct linked_list *l, struct generic_data d, struct generic_data s)
{
	if(l->size==0)
		return -1;
	
	/* pos is the index of the element pointed to by it */
	int pos = 0;
	struct node *it = l->head, *ins = malloc(sizeof *ins);
	while(it && !EQUAL(it->data, d)) {
		it = it->next;
		pos++;
	}
	/* it is pointing to the NULL at the end:
	 * the last element index is l->size-1 */
	if(pos==l->size)
		return -1;

	ins->next = it->next;
	ins->data = s;
	it->next = ins;
	l->size++;
	return pos+1;
}	
	
struct node* ll_recursive(struct node *it, struct generic_data d, struct generic_data s)
{
	struct node *next;	
	if(!EQUAL(it->data, d)) {
		if(it->next) {
			if(next=ll_recursive(it->next, d, s)) {
				it->next = next;
				return it;
			} else
				return NULL;
		} else 
			return NULL;
	} else {
		struct node *new = malloc(sizeof *new);
		new->data = s;
		new->next = it;
		return new;
	}
}		

int ll_insert_before(struct linked_list *l, struct generic_data d, struct generic_data s)
{
	struct node *next;
	if(!l->size)
		return -1;

	if(next=ll_recursive(l->head, d, s)) {
		l->head = next;
		l->size++;
		return 1;
	} else
		return -1;
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

struct linked_list* ll_init()
{
	struct linked_list *l = malloc(sizeof *l);	
	l->head = NULL;
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
