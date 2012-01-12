/*
 * Resizable array implementation 
 * The index of the array starts at 0(zero)
 * 
 * Error messages should be as specific as possible
 */

#include "resizable_array.h"

struct resizable_array* ra_init_capacity(size_t cap) {
	if(cap<=0) {
		mds_error(E_ILLEGAL_ARGUMENT, "Size of array must be greater than zero");
		return NULL;
	}

	/* Possibly check if the total size of memory 
	 * being allocated is larger than a threshold */	

	struct resizable_array *ra = malloc(sizeof(*ra));
	if(!ra) {
		mds_error(E_MALLOC_NULL, "Could not allocate memory");   	
		return NULL;
	}
	ra->cap = cap;
	ra->size = 0;
	ra->list = (ra->cap)*malloc(sizeof(*ra->list));

	/* Optional
	int i;
	for(i=0; ++i<=ra->size; )
		memcpy(ra->list[i], NULL, sizeof(struct generic_data*));
	ra->size = 0;
	*/

	return ra;
}

struct resizable_array* ra_init() {
	return ra_init_capacity(RA_INITLIST);
}

/* Increase by doubling
 * (a=2) */
void ra_inc(struct resizable_array *ra)
{
	struct generic_data *n_list;
	if(ra->cap == RA_MAXLIST) {
		mds_error(E_RA_MAX_CAPACITY, "Reached maximum capacity");
		return;
	}
	/* Either set every new entry to NULL
	 * or malloc() it*/
	/* Optional
	extracap = ncap - ra->cap;
	struct generic_data *nlist[extracap];
	nbytes = extracap * sizeof(struct generic_data*);
	struct generic_data **start = &ra->list[ra->cap];
	memcpy(start, nlist, nbytes);
	*/
	n_list = realloc(ra->list, 2*ra->cap*sizeof(*ra->list));
	if(!n_list) {
		mds_error(E_MALLOC_NULL, "Could not increase the size of the array");
		return;
	}
	ra->list = n_list;
	ra->cap = 2*ra->cap;
}

/* Decrease to a quarter
 * */
void ra_dec(struct resizable_array *ra)
{
	struct generic_data *n_list = realloc(ra->list, (ra->cap/2)*sizeof(*ra->list));
		/* Optional
		struct generic_data *nlist[ncap];
		memcpy(nlist, ra->list, ra->size);
		memcpy(ra->list, nlist, ncap);
		*/
	/* This should not happen */
	if(!n_list) {
		mds_error(E_MALLOC_NULL, "Could not decrease the size of the array");
		return;
	} 
	ra->list = n_list;
	ra->cap = ra->cap/2;
}

void ra_insert(struct resizable_array *ra, struct generic_data data, int pos) {
	int i;
	if(pos<0 || pos>ra->size)
		mds_error(E_ILLEGAL_ARGUMENT, "Position inexistent");

	if(ra->size==ra->cap)
		ra_inc(ra);

	for(i=ra->size; --i>=pos; )
		ra->list[i+1] = ra->list[i];

	ra->list[pos] = data;
	ra->size++;
}

/* Data should be malloc()'ed
 * before being added to the list */
struct generic_data ra_remove(struct resizable_array *ra, int pos) {
	if(ra_isEmpty(ra)) {
		mds_error(0, "Empty list");
		return;
	}
	if(pos<0 || pos>ra->size-1) {
		mds_error(E_ILLEGAL_ARGUMENT, "Position inexistent");
		return;
	}

	int i;
	struct generic_data data = *list[pos];
	for(i=pos; i++<ra->size-1; )
		ra->list[i] = ra->list[i+1];
	ra->size--;

	if(ra->size<=ra->cap/4)
		ra_dec(ra);
	return data;
}

size_t ra_size(struct resizable_array *ra) {
	return ra->size;
}

uchar_t ra_isEmpty(struct resizable_array *ra) {
	return (ra_size(ra)==0);
}
/* Positions returned: from 0 to n-1 */
void ra_walk(struct resizable_array *ra, (void*)(*f)(struct generic_data data)) {
	int i;
	if(!ra->size)
		return;
	for(i=-1;++i<ra->size; )
		if(!f(*ra->list[i]))
			break;
	return i;
}
