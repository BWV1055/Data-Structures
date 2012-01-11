/*
 * Linked list definition and basic operations declaration
 */

#ifndef _RESIZABLE_ARRAY_H_
#define _RESIZABLE_ARRAY_H_
/* Whether to check if standard C90 headers exist (taken from Autoconf 2.68 doc):
 * This macro is obsolescent, as current systems have conforming header files. 
 * New programs need not use this macro. */
#include <stdlib.h> /* free() */
#include <stddef.h>
#include <string.h> /* memcpy() */
#include "generic_data.h"


#define RA_INITLIST 1
#define RA_MAXLIST	128

//for large arrays with big structs
struct resizable_array {
	int size;
	int cap;
	struct generic_data* list[RA_INITLIST];
};

//create own separate implementation
struct resizable_array_small {
	int size;
	int cap;
	struct generic_data list[RA_INITLIST];
};

void ra_insert(struct resizable_array*, struct generic_data*, int);
struct generic_data ra_remove(struct resizable_array*, int);

struct resizable_array* ra_init();
void ra_walk(struct resizable_array*, void (*)(struct generic_data));

size_t ra_size(struct resizable_array*);
int ra_isEmpty(struct resizable_array*);

#endif
