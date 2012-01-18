/*
 * Hash table operations
 * 	This hash table is an implementation of the Map ADT
 * 	There are additional methods to:
 * 		add a large collection of objects to the hash table
 * 		clear the hash table
 *
 */

#include "hash_table.h"

hash_tbl_t* ht_init() {
	hash_func_t *predef_f = malloc(sizeof(predef_f));
	predef_f->hash = hash_code_fnv1;
	predef_f->compress = compress_mad;
	return ht_init_hash(predef_f);
}

hash_tbl_t* ht_init_hash(hash_func_t *hash_it) {
	hash_table *n_ht = malloc(sizeof(*n_ht));
	n_ht->func = malloc(sizeof(*n_ht->func));
	n_ht->func = *hash_it;
	n_ht->buckets = ba_init();
}

void ht_delete(hash_tbl_t *h) {
	free(h->func);
	free(h->buckets);
	free(h);
}

size_t ht_size(hash_tbl_t *h) {
	return h->buckets->size;
}

char ht_isEmpty(hash_tbl_t *h) {
	return (h->buckets->size==0);
}

int ht_get(hash_tbl_t *h, key_t qKey) {
	uint32_t b_number = h->func->compress(h->func->hash(qKey));
	struct generic_data *d = ba_get(h->buckets, b_number, qKey);
	return d->value;
}

void ht_put(hash_tbl_t *h, key_t nKey, int nValue) {
	uint32_t b_number = h->func->compress(h->func->hash(nkey));
	struct generic_data d;
	if(ba_get(h->buckets, b_number, nKey) == NULL) {
		d.key = key;
		d.value = value;
		ba_insert(h->buckets, d, b_number); 
	} else
		ba_set(h->buckets, b_number, key, value);
}

int ht_remove(hash_tbl_t *h, key_t qKey) {
	uint32_t b_number = h->func->compress(h->func->hash(qKey));
	struct generic_data *result = ba_get(h->buckets, b_number, qKey);
	if(result==NULL)
		return NULL;
	else {
		ba_remove(h->buckets, b_number, qKey);
		return result->value;
	}
}

void ht_keySet(hash_tbl_t *h, key_t *keySet, size_t *len) {
	int i, j=0;
	for(i=0;i<h->a->cp;i++) {
		ll_cursor c = h->buckets->ar[i].head;
		while(c->next) {
			*keySet[j++] = c->next->data.key;
			c = c->next;
		}
	}
	*len = h->a->size;
}

void ht_values(hash_table *h, int* values, int* len) {
	int i, j=0;
	for(i=0;i<h->a->cp;i++) {
		ll_cursor c = h->a->ar[i].head;
		while(c->next) {
			*values[j++] = c->next->data.value;
			c = c->next;
		}
	}
	*len = h->a->size;
}

void ht_entrySet(hash_table *h, struct generic_data* entries, int* len) {
	int i;
	for(i=0;i<h->a->cp;i++) {
		ll_cursor c = h->a->ar[i].head;
		while(c->next) {
			*entries[j++] = c->next->data;
			c = c->next;
		}
	}
	*len = h->a->size;
}
