/*
 * Skip list definition and operations, implements and ordered map
 * 	Most of the operations of the skip list are similar
 * 	to the operations of the ordered search tables
 * Uses a random number generator to select the position of an entry
 * 	Get returns in expected time O(log n), while put returns in worst-case time O(log n)
 * 
 * below and above can be implemented using an array of 0s and 1s
 * another implementation would be with doubly linked lists aligned at towers,
 * 	which would also be doubly linked lists
 *
 */

#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_

#include "../mds/mds_data_types.h"

#define SL_MAX_SIZE		1024

#define SL_MINUS_INF	0x00
#define SL_PLUS_INF		0xff

struct sl_node {
	struct generic_data data;
	struct sl_node *next;
	struct sl_node *prev;
	struct sl_node *below;
	struct sl_node *above;
};

/* The position ADT */
/* typedef (struct sl_node*)position sl_cursor; */
typedef struct sl_node* sl_cursor;

struct sl_list {
	sl_node head;
	sl_node tail;
	uchar_t len;
	uchar_t level;
};

struct sl {
	struct sl_list* lists;
	uchar_t height;
	uchar_t size;
};

/* Returns a newly initialized skip list */
struct sl* sl_init();
/* Returns a newly initialized skip list with one node containing data */
struct sl* sl_init_data(struct generic_data data);
/* Returns the number of elements in the skip list */
uchar_t sl_size(struct sl *l);
/* Returns 0 if the skip list is non empty, or greater than 0 (zero) if skip list is empty */
uchar_t sl_isEmpty(struct sl *l);
/* Returns the position following cur on the same level, NULL if no next position */
sl_cursor sl_next(sl_cursor cur);
/* Returns the position preceding cur on the same level, NULL if no previous position */
sl_cursor sl_prev(sl_cursor cur);
/* Returns the position below cur on the same tower, NULL if no below position */
sl_cursor sl_below(sl_cursor cur);
/* Returns the position above cur on the same tower, NULL if no above position */
sl_cursor sl_above(sl_cursor cur);
/* Adds a new data element in the skip list */
void sl_insert(struct sl *l, struct generic_data data);
/* Removes the element data from the skip list based on the qKey */
void sl_remove(struct sl *l, key_t qKey);
/* Returns the value associated with key qKey */
uint_t sl_get(struct sl *l, key_t qKey);
/* Sets a new value for key qKey */
void sl_set(struct sl *l, key_t qKey, uint_t value);

/* Joins two skip lists and returns a new skip list */
struct sl* sl_join(struct sl *l1, struct sl *l2);
/* Removes a section of a skip list 
 * The section starts at the first key greater or equal to sKey and 
 * ends at the first position less or equal to fKey */
void sl_remove_section(struct sl *l, key_t sKey, key_t fKey);


#endif
