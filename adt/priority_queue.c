/*
 *	Priority queue method implementation
 *
 */

#include "priority_queue.h"

pqueue_t* pq_init() {
	pqueue_t *qn = malloc(sizeof(*qn));
	qn->list = malloc(sizeof(*qn->list));
	qn->flags = 0;
	qn->last_op = 0;
	return qn;
}

struct generic_data pq_min(pqueue_t *q) {
	if(pq_isEmpty(q)) {
		mds_error(E_PQUEUE_EMPTY, "Priority queue is empty");
		return;
	}
	return dll_get(q->list, 1);
}

struct generic_data pq_insert(pqueue_t *q, key_t key, int value) {
	/* tempKey and pos are used to communicate with dll_compare_value from doubly_linked_list.c */
	extern key_t tempKey = key;
	extern pos;
	dll_walk(q->list, dll_compare_value);
	struct generic_data new;
	new.key = key;
	new.value = value;
	dll_insert(q->list, new, pos+1);
	return new;
}

struct generic_data pq_remove_min(pqueue_t *q) {
	if(pq_isEmpty(q)) {
		mds_error(E_PQUEUE_EMPTY, "Priority queue is empty");
		return;
	}
	return dll_remove(q->list, 1);
}	

size_t pq_size(pqueue_t *q) {
	return q->list->size;
}

uchar_t pq_isEmpty(pqueue_t *q) {
	return (pq_size(q)==0);
}

void pq_print(pqueue_t *q) {

}
