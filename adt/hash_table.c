/*
 * Hash table operations
 * 	This hash table is an implementation of the Map ADT
 * 	There are additional methods to:
 * 		add a large collection of objects to the hash table
 * 		clear the hash table
 *
 */

#include "hash_table.h"
/* Returns a newly initialized hash table using FNV-1 and MAD */
hash_tbl_t* ht_init() {
	hash_func_t predef_f;
	predef_f.hash = hash_code_fnv1;
	predef_f.compress = compress_mad;
	return ht_init_hash(predef_f);
}
/* Returns a newly initialized hash table, using hash_it as hash function */
hash_tbl_t* ht_init_hash(hash_func_t hash_it) {
	hash_table *n_ht = malloc(sizeof(*n_ht));
	n_ht->f = *f;
	n_ht->buckets =* ba_init();
}
/* Returns the number of elements stored in the hash table */
size_t ht_size(hash_tbl_t *h) {
	return h->buckets->size;
}
/* Returns 0 if hash table has elements, 1 otherwise */
uchar ht_isEmpty(hash_tbl_t *h) {
	return (h->buckets->size==0);
}
/* Returns the value stored for key qKey */
int ht_get(hash_tbl_t *h, key_t qKey) {
	uint b_number = h->func.compress(h->func.hash(key));
	struct generic_data d = ba_get(&h->a, b_number, key);
	return d.value;
}
/* If nValue is not present, add it, 
 * otherwise replace the existing value with this new one */
void ht_put(hash_tbl_t *h, key_t nKey, int nValue) {
	uint b_number = h->func.compress(h->func.hash(key));
	struct generic_data d;
	if(ba_get(&h->a, bucket_number, key) == NULL) {
		d.key = key;
		d.value = value;
		ba_insert(&h->a, d, b_number); 
	} else
		ba_set(&h->a, b_number, key, value);
}
/* Remove and return the value with key key; if there is no such key, return NULL */
int ht_remove(hash_tbl_t *h, key_t key) {
	uint bucket_number = h->f.compress(h->f.hash(key, key_l));
	struct generic_data *result = ba_get(&h->a, bucket_number, key, key_l);
	if(result==NULL)
		return NULL;
	else {
		ba_remove(&h->a, bucket_number, key, key_l);
		return result->value;
	}
}
/* Returns a collection (could be iterable?) of all keys stored in the hash table */
void ht_keySet(hash_tbl_t *h, key_t *keySet, size_t *len) {
	int i, j=0;
	for(i=0;i<h->a->cp;i++) {
		ll_cursor c = h->a->ar[i].head;
		while(c->next) {
			*keySet[j++] = c->next->data.key;
			c = c->next;
		}
	}
	*len = h->a->size;
}
/* Returns a collection of all values stored in the hash table */
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

/* Returns a collection of all key-value pairs in the hash table */
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
