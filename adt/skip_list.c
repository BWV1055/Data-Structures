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
/* Inserts and returns a new element above the current one and creates all the links */
sl_cursor sl_insertAbove(sl_cursor cur) {
	struct sl_node* tower_elem = malloc(sizeof(*tower_elem));
	tower_elem->data = cur->data;
	tower_elem->below = cur;
	cur->above = tower_elem;
	tower_elem->above = NULL;
	cur = cur->prev;
	while(!cur->above)
		cur = cur->prev;
	tower_elem->prev = cur->above;
	cur = tower_elem->below->next;
	while(!cur->above)
		cur = cur->next;
	tower_elem->next = cur->above;
	return tower_elem;
}
/* Finds the position with the smallest key larger than the data key */
sl_cursor sl_zigzag(sl_cursor cur, struct generic_data data) {
	while(G_DATA_GREATER(cur.data, data)) {
		if(cur->below)
			cur = cur->below->prev;
		else break;
	}
	while(cur->below)
		cur = cur->below;
	return cur;
}

void sl_insert(struct sl *l, struct generic_data data) {
	uchar_t i = 0, cl = l->height-1;
	struct sl_node *n = malloc(sizeof(*n));
	sl_cursor cur = l->lists[cl].tail;
	cur = sl_zigzag(cur, data);

	if(G_DATA_EQUAL(data, cur.data)) {
		mds_error(E_ILLEGAL_ARGUMENT, "Got a similar key");
		return;
	}

	/* dll_insert((struct dl_list*)l->lists[0], cur->prev, n) */
	n->prev = cur->prev;
	cur->prev->next = n;
	n->next = cur;
	cur->prev = n;
	n->below = n->above = NULL;
	n->data = data;

	cur = n;
	while(rand()%2) {
		if(i>cl) {
			l->lists[l->height] = make_list(l, l->height);
			sl_insertAbove(cur);
			break;
		}
		cur = sl_insertAbove(cur);
		i++;
	}
}

void sl_remove(struct sl *l, key_t qKey) {
	sl_cursor tempCur, cur = l->lists[l->height-1];
	struct generic_data *d = malloc(sizeof(*d));
	d->key = qKey;
	cur = sl_zigzag(cur, d);
	if(!G_DATA_EQUAL(cur, d)) {
		mds_error(E_ILLEGAL_ARGUMENT, "Could not find key");
		return;
	}
	do {
		tempCur = cur;
		cur->prev->next = cur->next;
		tempCur->next->prev = cur->prev; 
		free(tempCur);
		cur = cur->above;
	} while(cur=cur->above);
}
		
