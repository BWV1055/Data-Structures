/*
 * Skiplist definition and methods declaration
 * This list implements all the methods of the singly linked list
 * See http://en.wikipedia.org/wiki/Skip_list#Indexable_skiplist
 *
 *
 */

#ifndef _INDEXABLE_SKIP_LIST_H_
#define _INDEXABLE_SKIP_LIST_H_

struct node {
	struct generic_data* array;
	int ncap;
	int nsize;
	struct node *prev;
	struct node *next;
	struct node *below;
	struct node *above;
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
