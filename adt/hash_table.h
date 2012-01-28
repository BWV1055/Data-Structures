/*
 * Hash table operations
 * 	This hash table is an implementation of the Map ADT
 *	(The distinction between a Map and a Dictionary is that the keys
 *		in a Map form a Set - are unique, while in a Dictionary form
 *		a Collection - the same key can appear multiple times)
 * 	There are additional methods to:
 * 		add a large collection of objects to the hash table
 * 		clear the hash table
 *
 */

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "../bds/bucket_array.h"

typedef ulong (*hash_code_func_t)(key_t key);
typedef uint (*compress_func_t)(ulong code);


typedef struct {
	hash_code_func_t hash;
	compress_func_t compress;
} hash_func_t;

typedef struct {
	struct bucket_array *buckets;
	hash_func_t *func;
} hash_tbl_t;

/* Returns a newly initialized hash table using FNV-1 and MAD */
hash_tbl_t* ht_init();
/* Returns a newly initialized hash table, using hash_it as hash function */
hash_tbl_t* ht_init_func(hash_func_t hash_it);
/* Frees the memory allocated for a hash table initialized with ht_init() */
void ht_delete(hash_tbl_t *h);
/* Returns the number of elements stored in the hash table */
size_t ht_size(hash_tbl_t *h);
/* Returns 0 if hash table has elements, 1 otherwise */
char ht_isEmpty(hash_tbl_t *h);
/* Removes all entries in the hash table */
void ht_clear(hash_tbl_t *h);
/* Returns the value stored for key qKey */
int ht_get(hash_tbl_t *h, key_t qKey);
/* If nValue is not present, add it, 
 * otherwise replace the existing value with this new one */
void ht_put(hash_tbl_t *h, key_t nKey, int nValue);
/* Adds a large number of entries at once in the hash table
 * Faster than calling ht_put for each entry */
void ht_multiple_put(hash_tbl_t *h, struct generic_data *entrySet, size_t *len);
/* Remove and return the value with key qKey; if there is no such key, return NULL */
int ht_remove(hash_tbl_t *h, key_t qKey);
/* Returns in keySet a set of all keys stored in the hash table */
void ht_keySet(hash_tbl_t *h, key_t *keySet, size_t *len);
/* Returns in values a collection of all values stored in the hash table */
void ht_values(hash_tbl_t *h, int *values, size_t *len);
/* Returns in entrySet a collection containing all the key-value entries in the hash table 
 * Entries can be sorted using a comp_func_t function */
void ht_entrySet(hash_tbl_t *h, struct generic_data *entrySet, size_t *len);

/* Below are provided some hash functions and compression methods */

/* The hash code returned is the memory location of the key of the data entry 
 * This could change if there is a garbage collector (if possible, rehash after
 * 		calling the gc)
 * Also, for similar strings, this function will generate different results */
uint32_t hash_code_mem_loc(key_t *key) {
	return (uint32_t)key;
}
/* FNV-1 32 bit hashing algorithm
 * Very fast */
uint64_t hash_code_fnv1(key_t key) {
	uint32_t fnv_prime = 16777619, offset_basis = 2166136261;
   	uint64_t hash_code = offset_basis;
	int i; 
	for(i=0;i<key.len;i++) {
		hash_code *= fnv_prime;
		hash_code ^= key.name[i];
	}
	return hash_code;
}
/* MAD compression function */
uint32_t compress_mad(uint64_t code, uint32_t ba_size) {
	uint64_t p = 2305843009213693951;
	return ((101*code+41)%p)%ba_size;
}

#endif
