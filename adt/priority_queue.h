/*
 *	Priority queue data structure and method definition
 *	This priority queue is implemented using a sorted doubly linked list.
 *	If the size of the priority queue is small, sometimes its better to use
 *		an unsorted linked list.
 *	The order between entries is determined by stcmp()'ing the keys, there can
 *		be multiple entries with the same key (entries form a collection).
 *
 *
 *
 */

#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "../bds/doubly_linked_list.h"

#define PRIORITY_QUEUE_CAPACITY		512

#define PRIORITY_QUEUE_OP_INSERT	(1<<0)
#define PRIORITY_QUEUE_OP_REMOVE	(1<<1)
#define PRIORITY_QUEUE_OP_MIN		(1<<2)

typedef struct {
	struct doubly_linked_list *list;
	uchar_t flags;
	uchar_t last_op;
} pqueue_t;

/* Returns a newly initialized priority queue */
pqueue_t* pq_init();
/* Returns an entry with the minimum key, but does not remove it */
struct generic_data pq_min(pqueue_t *q);
/* Inserts a new key-value pair in the priority queue, and returns the associated entry */
struct generic_data pq_insert(pqueue_t *q, key_t key, int value);
/* Removes and returns an entry with the minimum key */
struct generic_data pq_remove_min(pqueue_t *q);
/* Returns the total number of entries of the priority queue */
size_t pq_size(pqueue_t *q);
/* Returns 0 if the pqueue is empty, 1 otherwise */
uchar_t pq_isEmpty(pqueue_t *q);
/* Prints the values of the entries in a pqueue, in increasing priority order */
void pq_print(pqueue_t *q);

#endif
