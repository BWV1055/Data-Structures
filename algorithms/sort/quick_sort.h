/*
 * Quick sort function declaration
 */

#include "../../mds/mds_errors.h"
#include "../../mds/mds_data_types.h"

void quick_sort(int len; struct generic_data ar[len], int len);

#define SWAP(a, b, size) \
	do { \
		register size_t __size = (size); \
		register char* __a = (a), * __b = (b); \
		do { \
			char __temp = *__a; \
		   	*__a++ = *__b; \
			*__b++ = __temp; \
		} while(--__size>0); \
	}while(0) 


