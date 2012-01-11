/*
 * Generic data definition
 */

#ifndef _GENERIC_DATA_H_
#define _GENERIC_DATA_H

struct generic_data {
	int val;
};

#define EQUAL(a,b) ((a).val==(b).val?1:0)

#endif
