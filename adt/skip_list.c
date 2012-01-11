/*
 *	Skip list operations implementation
 *
 *
 *
 */

#include "skip_list.h"

sl_cursor make_sentinel(uchar_t type) {
	sl_node *sen = malloc(sizeof(*sen));
	struct generic_data data;
	key_t tempKey;
	tempKey.name = type ? G_DATA_MIN : G_DATA_MAX;
	tempKey.len = 0;
	data.key = tempKey;
	data.value = 0;
	sen->data = data;
	sen->below = sen->above = sen->prev = sen->next = NULL;
	return sen;
}

sl_list* make_list(struct sl *l, uchar_t level) {
	uchar_t cl = l->height-1;
	sl_list *list = malloc(sizeof(*list));

	list->head = make_sen(0);
	list->tail = make_sen(1);
	list->head->next = list->tail;
	list->tail->next = list->head;
	/* Stack a new list on top */
	list->head->below = l->lists[cl].head;
	l->lists[cl].head->above = list->head;
	list->tail->below = l->lists[cl].tail;
	l->lists[cl].tail->above = list->tail;

	list->len = 0;
	list->level = level;
	return list;
}

struct sl* sl_init() {
	struct sl *l = malloc(sizeof(*n));

	l->lists = malloc(sizeof(l->lists));
	l->lists[0] = make_list(l, 0);
	l->height = 1;
	l->size	= 0;
	return l;
}

struct sl* sl_init_data(struct generic_data data) {
	struct sl *l = sl_init();
	struct sl_node *n = malloc(sizeof(*n));
	n->data = data;
	n->above = n->below = NULL;
	n->prev = l->lists[0].head;
	n->next = l->lists[0].tail;
	l->lists[0].head->next = n;
	l->lists[0].tail->prev = n;
	return l;
}

inline uchar_t sl_size(struct sl *l) {
	return l->size;
}

inline uchar_t sl_isEmpty(struct sl *l) {
	return (l->size==0);
}

inline sl_cursor sl_next(sl_cursor cur) {
	return cur->next;
}

inline sl_cursor sl_prev(sl_cursor cur) {
	return cur->prev;
}

inline sl_cursor sl_below(sl_cursor cur) {
	return cur->below;
}

inline sl_cursor sl_above(sl_cursor cur) {
	return cur->above;
}

void sl_insert(struct sl *l, struct generic_data data) {
	uchar_t i = 0, cl = l->height-1;
	struct sl_node *n = malloc(sizeof(*n));
	sl_cursor cur = l->lists[cl].tail;
	while(G_DATA_GREATER(cur.data, data)) {
		if(cur->below)
			cur = cur->below->prev;
		else
			break;
	}

	if(G_DATA_EQUAL(data, cur.data)) {
		mds_error(E_ILLEGAL_ARGUMENT, "Got a similar key");
		return;
	}

	while(cur->below)
		cur = cur->below;
	
	/* dll_insert((struct dl_list*)l->lists[0], cur->prev, n) */
	n->prev = cur->prev;
	cur->prev->next = n;
	n->next = cur;
	cur->prev = n;
	while(rand()%2) {
		if(i>=cl) {
			cl = (++l->height)-1;
			l->lists[cl] = make_list(cl);
			/* To be completed */
		}
	}

}
