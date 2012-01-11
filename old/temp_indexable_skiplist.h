/*
 * Indexable skiplist (Razvan style) definition and methods declaration
 * The basic idea is to use an unrolled linked list with a variable number of elements in each node
 * The number of elements in each node increases two-fold for each new node (ie 1, 2, 4, 8,...)
 * Resizing the skiplist follows the same principles as for resizable arrays:
 *		If the list is full, add a new node with size equal to all the previous nodes		
 *		When a node is removed and the size<capacity/4, remove the last node
 *
 */

#ifndef _INDEXABLE_SKIPLIST_H_
#define _INDEXABLE_SKIPLIST_H_

struct node {
	struct generic_data* array;
	int ncap;
	int nsize;
	struct node *prev;
	struct node *next;
};

struct indexable_skiplist {
	struct node *head;
	int cap;
	int size;
	struct node *tail;
};

void is_insert(struct indexable_skiplist *l, struct generic_data d, int i);
struct generic_data is_remove(struct indexable_skiplist *l, int i);

struct indexable_skiplist* is_init();
void is_walk(struct indexable_skiplist *l, void(*f)(struct generic_data));

#endif
