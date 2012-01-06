/*
 * Bucket array implementation of operations
 *
 */

#include "bucket_array.h"

struct bucket_array* ba_init() {
	int i;
	struct bucket_array* ba = malloc(sizeof(*ba));
	ba->size = 0;
	ba->cp = 16;
	struct linked_list **new_ar = malloc(sizeof(**new_ar));
	ba->ar = new_ar;
	for(i=0;i<ba->cp;i++)
		ba->ar[i] = ll_init();
	return ba;
}

uint ba_size(struct bucket_array *ba) {
	return ba->size;
}

uint ba_isEmpty(struct bucket_array *ba) {
	return (ba->size==0);
}

void ba_insert(struct bucket_array *ba, struct generic_data d, uint pos) {
	if(pos>=ba->cp) {
		mds_error(0, "Cannot insert at position %d", pos);
		return;
	}
	if(ba->ar[pos]->total == BA_MAX_BUCKET_SIZE) {
		mds_error(0, "Bucket %d is full", pos);
		return;
	}
	ll_cursor c = ba->ar[pos]->head;
	node *d_v = malloc(sizeof (*d_v));
	d_v->data = d;
	d_v->next = NULL;
	if(ba->ar[pos]->total==0) {
		ba->ar[pos]->head = d_v;
	} else {
		while(c->next)
			c = c->next;
		c->next = d_v;
	}
	ba->ar[pos]->total++;
	ba->size++;
}

void ba_remove(struct bucket_array *ba, uint pos, const char *d_key, uint d_key_l) {
	if(pos>=ba->cp) {
		mds_error(0, "Inexistent position %d", pos);
		return;
	}
	if(!ba->ar[pos]->total) {
		mds_error(0, "Empty bucket %d", pos);	
		return;
	}
	ll_cursor prev, c = ba->ar[pos]->head;
	ba->ar[pos]->total--;
	ba->size--;
	if(ba->ar[pos]->total==1) {
		free(ba->ar[pos]->head);
		return;
	}
	while(c->next && strcmp(c->next->data.key, d_key)) {
		prev = c;
		c = c->next;
	}
	if(strcmp(c->data.key, d_key))
		mds_error(0, "Could not find the key in bucket %d", pos);
	else {
		prev->next = c->next;
		free(c);
	}
}
/* Sets a new value for key d_key, if it exists */
void ba_set(struct bucket_array *ba, uint pos, const char *d_key, uint d_key_l, int value) {
	if(pos>=ba->cp) {
		mds_error(0, "Inexistent position %d", pos);
		return;
	}
	ll_cursor c = ba->ar[pos]->head;
	while(c->next && strcmp(c->data.key, d_key))
		c = c->next;
	if(!strcmp(c->data.key, d_key))
		c->data.value = value;
}
/* Returns NULL if there is no such key at position pos */
struct generic_data* ba_get(struct bucket_array *ba, uint pos, const char *d_key, uint d_key_l) {
	if(pos>=ba->cp) {
		mds_error(0, "Inexistent position %d", pos);
		return;
	}
	ll_cursor c = ba->ar[pos]->head;
	while(c->next && strcmp(c->data.key, d_key))
		c = c->next;
	if(strcmp(c->data.key, d_key)) {
		mds_error(0, "Could not find the key", pos);
		return NULL;
	}
	return &c->data;
}
	
void ba_increase(struct bucket_array *ba) {
	if(2*ba->cp > BA_MAX_SIZE) {
		mds_error(0, "Reached maximum capacity");
		return;
	}
	int i;
	struct linked_list* n_ar[2*ba->cp];
	for(i=0;i<ba->cp;i++)
		n_ar[i] = ba->ar[i];
	ba->cp = 2*ba->cp;
	for( ;i<ba->cp;i++)
		n_ar[i] = ll_init();
	ba->ar = n_ar;
}

void ba_decrease(struct bucket_array *ba) {
	/* Checking is done in the method which calls ba_decrease */
	struct linked_list* n_ar[ba->cp/2];
	int i;
	for(i=0;i<ba->cp/2;i++)
		n_ar[i] = ba->ar[i];
	ba->cp = ba->cp/2;
	ba->ar = n_ar;
}
