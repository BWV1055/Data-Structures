/*
 * Circularly linked list definition and basic operations declaration
 */

#ifndef _CIRCULARLY_LINKED_LIST_H_
#define _CIRCULARLY_LINKED_LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include "generic_data.h"

struct node {
	struct generic_data data;
	struct node* next;
};

struct circularly_linked_list {
	int size;
	struct node* cur;
};

void cll_insert(struct circularly_linked_list*, struct generic_data, int);
struct generic_data cll_remove(struct circularly_linked_list*, int);

size_t cll_size(struct circularly_linked_list*);
int cll_isEmpty(struct circularly_linked_list*);

struct circularly_linked_list* cll_init();
void cll_walk(struct circularly_linked_list*, void (*)(struct generic_data));

#endif
