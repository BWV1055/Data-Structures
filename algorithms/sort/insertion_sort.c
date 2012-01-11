/*
 * Insertion sort implementation
 */

#include "insertion_sort.h"

void sort_insertion(struct generic_data* ar, size_t size)
{
	if(size<=0)
		mds_error(0, "Non-positive array size");

	if(size==1) 
		return;

	int i, j;
	struct generic_data cur;
	for(i=1;i<size;i++) {
		cur = ar[i];
		j = i-1;
		while((j>=0) && GREATER(ar[j],cur)) 
			ar[j+1] = ar[j--];
		ar[j+1] = cur;
	}
}
