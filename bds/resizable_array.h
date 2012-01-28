/*
 * Resizable array definition and operations declaration
 */

#ifndef _RESIZABLE_ARRAY_H_
#define _RESIZABLE_ARRAY_H_
/* Whether to check if standard C90 headers exist (taken from Autoconf 2.68 doc):
 * This macro is obsolescent, as current systems have conforming header files. 
 * New programs need not use this macro. */

#include "../mds/mds_data_types.h"
#include "../mds/mds_errors.h"

#define RA_INIT_SIZE 		128
#define RA_MAX_SIZE			2048

//for large arrays with big structs
struct resizable_array {
	size_t size;
	size_t cap;
	struct generic_data* list;
};

//create own separate implementation
struct resizable_array_small {
	size_t size;
	size_t cap;
	struct generic_data list[RA_INITLIST];
};

typedef (void*)(*ra_walk_f)(struct generic_data, void*, void*);

/* Returns a new resizable array with RA_INIT_SIZE positions */
struct resizable_array* ra_init();
/* Returns a newly initialized resizable array with initial capacity cap */
struct resizable_array* ra_init_cap(size_t cap);
/* Inserts data at position pos */
void ra_insert(struct resizable_array *ra, int pos, struct generic_data data);
/* Removes and returns the element at position pos */
struct generic_data ra_remove(struct resizable_array *ra, int pos);
/* Returns the element at position pos without removing it, similar to ra->list[pos] */
struct generic_data ra_get(struct resizable_array *ra, int pos);
/* Sets the element at position pos; rewrites the present value if there is one
 * If the position is greater than the array capacity, the array is increased accordingly */
void ra_set(struct resizable_array *ra, int pos, struct generic_data data);
/* Walks through every element of ra and applies function f 
 * See the description for ll_walk in linked_list.h for more details on f */
void* ra_walk(struct resizable_array *ra, ra_walk_f f);
/* Returns the number of elements stored in ra */
size_t ra_size(struct resizable_array *ra);
/* Returns 0 if there are elements in the array, greater than zero otherwise */
uchar_t ra_isEmpty(struct resizable_array *ra);

#endif
