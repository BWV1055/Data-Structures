/*
 *	Linked list header file
 *
 * Linked list definition and basic operations declaration
 * The list of methods defined here is used in all linked list data structures,
 * with possible additions in more sophisticated linked lists types
 * This is the basic singly linked list, it stores a pointer in the head field
 *
 * The interface works with data, NOT with nodes, so that someone cannot tamper
 * the list (by accessing the next field, for example). This has some consequences
 * on the operations available on the list:
 * - the insert and remove functions cannot specify a node, only an index to insert
 *   after (to insert before, just decrease the index by one), or a value. 
 * - if a value is specified, the new data will be inserted after or before 
 *	 the FIRST occurence of the value specified 
 * - in the future, there will be functions to insert/remove before/after the last
 *   occurence of the specified value, or before/after the nth occurence
 *
 * There is a double guard against out of bounds elements:
 * 1) a size field equal to the number of elements in the list
 * 2) the next field of the last elements points to NULL
 *
 * Errors: 
 *	For out of range indices, a message is printed to stderr (or a file)
 *  Malloc() errors (and other serious errors) result in program exiting
 */


#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

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

/* Returns the number of elements in the list */
int ll_size(struct linked_list *l);
/* Returns whether the list is empty or not */
int ll_isEmpty(struct linked_list *l);

/* Adds a new element in the list at position i, shifting elements right to make room */
void ll_insert(struct linked_list *l, struct generic_data d, int i);
/* Insert d after the first occurence of s and return the index of s, or return -1 if s is not found */
int ll_insert_after(struct linked_list *l, struct generic_data d, struct generic_data s);
/* Insert d before the first occurence of s; return 1 on success or -1 if s is not found */
int ll_insert_before(struct linked_list *l, struct generic_data d, struct generic_data s);
/* Wrapper function to prepend d to the list (ie: insert on the first position) */
void ll_insert_beginning(struct linked_list *l, struct generic_data d);
/* Wrapper function to append d to the list */
void ll_insert_end(struct linked_list *l, struct generic_data d);
/* Append list a to list l 
 * List a is NOT removed */
void ll_append(struct linked_list *l, struct linked_list *a);


/* Removes and returns the element at position i; shifts following
 * elements to the left one position */
struct generic_data ll_remove(struct linked_list* l, int i);

/* Returns the element at position i in the list, without removing it */
struct generic_data ll_get(struct linked_list* l, int i);
/* Returns the element at position i and replaces it with d */
struct generic_data ll_set(struct linked_list* l, struct generic_data d, int i);

/* Returns a newly created and initialized linked list */
struct linked_list* ll_init();
/* Walks the list and applies function f to every element in order */
void ll_walk(struct linked_list* l, void (*f)(struct generic_data));

/* Removes all the elements in the list */
void ll_clear(struct linked_list* l);
/* Returns an array with all the elements of the list in the same order */
struct generic_data* ll_toArray(struct linked_list* l);

/* Search and sort methods
 * Note: a function to compare two elements needs to be implemented */
/* Returns the index of the first element equal to d, or -1 */
int ll_indexOf(struct linked_list *l, struct generic_data d);
/* Returns the index of the last element equal to d, or -1 */
int ll_lastIndexOf(struct linked_list *l, struct generic_data d);
/* Sort the list according to cmp */
void ll_sort(struct linked_list *l);

#endif
