/*
 * Bucket array operations
 *	This is a variation of a dynamic array, where each array element
 *		holds a singly linked list and stores at most 4 data values
 *		(change DA_MAX_BUCKET_SIZE to increase the size of the linked list)
 *	This is generally used in hash tables.
 *	Hash collisions in the hash table used by this bucket array should be
 *		resolved using separate chaining
 *
 *
 *
 */

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BA_MAX_SIZE				1024
#define BA_MAX_BUCKET_SIZE		4

struct bucket_array {
	struct linked_list **ar;
	uint cp;
	uint size;
};
/* Returns a newly initialized bucket array; this is the way to start */
struct bucket_array* ba_init();
/* Returns the number of data values in the array */
uint ba_size(struct bucket_array *ba);
/* Returns 0(zero) if array is empty (no elements), 1 otherwise */ 
uint ba_isEmpty(struct bucket_array *ba);
/* Inserts an element in the array at position pos */
void ba_insert(struct bucket_array *ba, struct generic_data d, uint pos);
/* Removes an element from position pos and with key d_key */
void ba_remove(struct bucket_array *ba, uint pos, const char *d_key, uint d_key_l); 
/* Returns the key and value stored at position pos */
struct generic_data* ba_get(struct bucket_array *ba, uint pos, const char *d_key, uint d_key_l);
