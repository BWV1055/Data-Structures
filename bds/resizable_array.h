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

#define RA_INITLIST 		128
#define RA_MAXLIST			2048

//for large arrays with big structs
struct resizable_array {
	int size;
	int cap;
	struct generic_data* list;
};

//create own separate implementation
struct resizable_array_small {
	size_t size;
	size_t cap;
	struct generic_data list[RA_INITLIST];
};

/* Initializes an empty resizable array and returns it */
struct resizable_array* ra_init();
/* Returns a newly initialized resizable array with init_cap initial capacity */
struct resizable_array* ra_init_capacity(size_t init_cap);
/* Inserts data at position pos and shifts remaining elements right */
void ra_insert(struct resizable_array *ra, struct generic_data data, int pos);
/* Removes and returns the element at position pos */
struct generic_data ra_remove(struct resizable_array *ra, int pos);
/* Walks through every element of ra and applies function f 
 * See the description for ll_walk in linked_list.h for more details */
void ra_walk(struct resizable_array *ra, (void*)(*f)(struct generic_data));
/* Returns the number of elements stored in ra */
size_t ra_size(struct resizable_array *ra);
/* Returns 0 if there are elements in the array, greater than zero otherwise */
uchar_t ra_isEmpty(struct resizable_array *ra);

#endif
