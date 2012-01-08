/*
 * Doubly linked list module
 * 
 * Interface to a doubly linked list implementation
 * TODO: The behavior comment should also describe, for each prototype, every
 *       parameter and the return value (if any), and how they are interpreted.
 *       Here you are making a _contract_ that your module will speak a certain
 *       language when it communicates with external callers.
 *
 *
 *
 * Created by: Razvan
 */

#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include "generic_data.h"

struct node {
	struct generic_data data;
	struct node* next;
	struct node* prev;
};

struct doubly_linked_list {
	struct node *head;
	int size;
};

/*
 * Methods available to external callers
 */

/* Inserts a new node in the list at the specified position */
void dll_insert(struct doubly_linked_list*, struct generic_data, int);
/* Removes a node in the list from the specified position */
struct generic_data dll_remove(struct doubly_linked_list*, int);

/* Initializes a new doubly linked list */
struct doubly_linked_list* dll_init();
/* Walks the list and for each node, applies a function */
void dll_walk(struct doubly_linked_list*, void (*)(struct generic_data));

#endif
