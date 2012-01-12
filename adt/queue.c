/*
 *	Queue operation implementation
 *
 */

#include "queue.h"

queue_t* q_init() {
	queue_t *nq = malloc(sizeof(*nq));
	nq->list = malloc(sizeof(*nq->list));
	nq->flags = 0;
	nq->last_op = 0;
	return nq;
}

void q_enqueue(queue_t *q, struct generic_data data) {
	if(q_size(q)==QUEUE_MAX_CAPACITY) {
		mds_error(E_FULL_QUEUE, "Queue is full");
		return;
	}
	ll_insert_end(q->list, data);
}

struct generic_data q_dequeue(queue_t *q) {
	if(q_isEmpty(q)) {
		mds_error(E_EMPTY_QUEUE, "Queue is empty");
		return;
	}
	return ll_remove(q->list, q_size(q));
}

struct generic_data q_front(queue_t *q) {
	if(q_isEmpty(q)) {
		mds_error(E_EMPTY_QUEUE, "Queue is empty");
		return;
	}
	return ll_get(q->list, q_size(q));
}

size_t q_size(queue_t *q) {
	return q->list->total;
}

uchar_t q_isEmpty(queue_t *q) {
	return (q_size(q)==0);
}

void q_print(queue_t *q) {
	printf("Queue elements (front first):\n");
	ll_walk(q->list, ll_print_elem);
}








/* Example usage (old)
 *	Round robin scheduler
 * 	Each generic_data element could be considered as describing a process:
 * 	the key is the name of the process, the value is the PID */
void round_robin_scheduler(struct generic_data *processes, size_t total) {
	int i, total_time, temp;
	queue_t queue = q_init();
	for(i=0;i<total;i++)
		q_queue(processes[i]);

	for(total_time=0;total_time<3600;total_time++) {
		for(i=0;i<total;i++) {
			struct generic_data temp = q_dequeue();
			f_process(temp);
			q_enqueue(temp);
		}
	}

}

void f_process(struct generic_data process) {
	process.value = (process.value++)%1000;
}
