/*
 *	Queue data structure and methods definition
 *	This queue uses a linked list
 *
 *
 *
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../bds/linked_list.h"

#define QUEUE_MAX_CAPACITY		128		

#define QUEUE_OP_ENQUEUE			(1<<0)
#define QUEUE_OP_DEQUEUE			(1<<1)
#define QUEUE_OP_FRONT				(1<<2)

typedef struct {
	struct linked_list *list;
	uchar_t flags;
	uchar_t last_op;
} queue_t;

/* Returns a newly initialized queue */
queue_t* q_init();
/* Adds a new element at the end of the queue */
void q_enqueue(queue_t *q, struct generic_data data);
/* Returns the element at the front of the queue and removes it */
struct generic_data q_dequeue(queue_t *q);
/* Returns the element at the front of the queue, but does not remove it */
struct generic_data q_front(queue_t *q);
/* Returns the number of elements in the queue */
size_t q_size(queue_t *q);
/* Returns 0 if the queue is empty, 1 otherwise */
uchar_t q_isEmpty(queue_t *q);
/* Prints the elements in a queue, with the element at the front first */
void q_print(queue_t *q);

#endif
