/*
 * Resizable array implementation 
 * The index of the array starts at 0(zero)
 * 
 * Error messages should be as specific as possible
 */

#include "resizable_array.h"
#include <stdio.h>

struct resizable_array* ra_init_capacity(size_t cap)
{
	if(cap<=0) {
		mds_error(0, "Size of array must be greater than zero");
		return NULL;
	}

	/* Possibly check if the total size of memory 
	 * being allocated is larger than a threshold */	

	struct resizable_array *ra = malloc(sizeof *ra);
	if(ra==NULL)
		return NULL;

	/* Optional
	int i;
	for(i=0; ++i<=ra->size; )
		memcpy(ra->list[i], NULL, sizeof(struct generic_data*));
	ra->size = 0;
	*/
	ra->cap = cap;

	return ra;
}

struct resizable_array* ra_init()
{
	return ra_init_capacity(16);
}

/* Increase by doubling
 * (a=2) */
void ra_inc(struct resizable_array *ra)
{
	size_t nbytes, extracap, ncap = 2 * ra->cap;
	if(ncap > RA_MAXLIST)
		ncap = RA_MAXLIST;
	/* Either set every new entry to NULL
	 * or malloc() it*/
	/* Optional
	extracap = ncap - ra->cap;
	struct generic_data *nlist[extracap];
	nbytes = extracap * sizeof(struct generic_data*);
	struct generic_data **start = &ra->list[ra->cap];
	memcpy(start, nlist, nbytes);
	*/
	ra->cap = ncap;
}

/* Decrease to a quarter
 * */
void ra_dec(struct resizable_array *ra)
{
	if(ra->size<=ra->cap/4) {
		size_t ncap = ra->cap/2;
		/* Optional
		struct generic_data *nlist[ncap];
		memcpy(nlist, ra->list, ra->size);
		memcpy(ra->list, nlist, ncap);
		*/
		ra->cap = ncap;
	}
}

void ra_insert(struct resizable_array *ra, struct generic_data *d, int pos)
{
	if(pos<0)
		mds_error(1, "Cannot insert element at negative index");
	if(pos>ra->size)
		mds_error(1, "Insert new element with out of range index");

	if(ra->size==ra->cap)
		ra_inc(ra);

	struct generic_data **list = ra->list;
	int i;
	if(ra->size)
		for(i=ra->size; --i>=pos; )
			list[i+1] = list[i];

	list[pos] = d;
	ra->size++;
}

/* Data should be malloc()'ed
 * before being added to the list */
struct generic_data ra_remove(struct resizable_array *ra, int pos)
{
	if(ra_isEmpty(ra))
		mds_error(0, "Empty list");
	if(pos<0)
		mds_error(1, "Cannot delete element at negative index");
	if(pos>ra->size-1)
		mds_error(1, "Delete element with out of range index");

	struct generic_data **list = ra->list;
	struct generic_data data = *list[pos];
	int i;
	for(i=pos; i++<ra->size-1; )
		list[i] = list[i+1];
	ra->size--;

	if(ra->size<=ra->cap/4)
		ra_dec(ra);
}

size_t ra_size(struct resizable_array *ra)
{
	return ra->size;
}

int ra_isEmpty(struct resizable_array *ra)
{
	return (ra_size(ra)==0);
}

void ra_walk(struct resizable_array *ra, void (*f)(struct generic_data))
{
	if(ra->size) {
		int i;
		for(i=-1;++i<ra->size; )
			f(*ra->list[i]);
	}
}
