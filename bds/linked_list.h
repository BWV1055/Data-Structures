/*
 *	Linked list header file
 *
 */

#include <stdlib.h>
#include "../mds/mds_errors.h"

typedef unsigned int uint;

struct generic_data {
	char *key;
	uint key_l;
	int value;
};

typedef struct _node {
	struct generic_data data;
	struct _node *next;
} node;

struct linked_list {
	int total;
	node *head;
};

typedef node* ll_cursor;

struct linked_list* ll_init();
void insert_node(struct linked_list, struct generic_data, uint);
struct generic_data delete_node(struct linked_list, int); 
