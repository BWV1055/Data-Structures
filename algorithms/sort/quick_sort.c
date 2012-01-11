/*
 * Quick-sort implementation
 * This is a generic implementation
 * It sorts the values of an array
 */

#include "quick_sort.h"

void quick_sort(int len; struct generic_data ar[len], int len)
{
	if(len<0)
		mds_error(0, "Negative array length");
	if(len==1 || len==0)
		return;
	int i=0, j=0, k=0;
	struct generic_data l[len-1], g[len-1], e[len];
	struct generic_data piv = ar[len-1];
	while(--len>=0) {
		if(ar[len].val<piv.val) l[i++] = ar[len];
		else if(ar[len].val>piv.val) g[j++] = ar[len];
		else e[k++] = ar[len];
	}
	quick_sort(l, i);
	quick_sort(g, j);
	memcpy(ar, l, i*sizeof(struct generic_data));
	memcpy(&ar[i], e, k*sizeof(struct generic_data));
	memcpy(&ar[i+k+1], g, j*sizeof(struct generic_data));
}
	
