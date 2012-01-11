/*
 * Linked list definition and basic operations declaration
 */

#ifndef _LINKED_LIST_HEAD_H_
#define _LINKED_LIST_HEAD_H_

#include <stdlib.h>
#include <stdio.h>
#include "generic_data.h"

struct node {
	struct generic_data data;
	struct node* next;
};

struct linked_list {
	int size;
	struct node head;
	int is_set;
};

void ll_insert(struct linked_list*, struct generic_data, int);
struct generic_data ll_remove(struct linked_list*, int);

struct linked_list* ll_init();
void ll_walk(struct linked_list*, void (*)(struct generic_data));

#endif
