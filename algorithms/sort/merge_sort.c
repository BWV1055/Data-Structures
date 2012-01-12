/*
 * Merge-sort implementation
 * This is a generic implementation
 * It sorts the values of an array
 */

#include "merge_sort.h"

struct generic_data* mgs_r(struct generic_data *ar, int len)
{
	if(len==1)
		return ar;

	struct generic_data *ret = malloc(len*sizeof(struct generic_data*));
	struct generic_data *f = malloc((len+1)/2*sizeof(struct generic_data*));
	struct generic_data *s = malloc(len/2*sizeof(struct generic_data*));
	f = mgs_r(ar, (len+1)/2);
	s = mgs_r(&ar[(len+1)/2], len/2);
	int fp = 0, sp=0, i=0;
	for( ;sp<len/2 && fp<(len+1)/2; ) 
		ret[i++] = (f[fp].val<s[sp].val)?f[fp++]:s[sp++];
	while(sp<len/2) ret[i++] = s[sp++];
	while(fp<(len+1)/2) ret[i++] = f[fp++];
	return ret;
}
		
struct generic_data* merge_sort(struct generic_data *ar, int len)
{
	if(len<=0)
		mds_error(1, "Length has to be greater than zero");
	return mgs_r(ar, len);
}
