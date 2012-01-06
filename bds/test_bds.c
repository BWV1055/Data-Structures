/*
 *	This is a place where the basic data structures are tested
 *
 */

#include "bucket_array.h"

int main() {
	struct bucket_array* b = ba_init();
	struct generic_data d;
	d.key = "music";
	d.key_l = 5;
	d.value = 2;
	printf("This new bucket has %d elements.\n", ba_size(b));

	ba_insert(b, d, 4);
	printf("Now, this bucket has %d elements.\n", ba_size(b));
	struct generic_data *p_d = ba_get(b, 4, "music", 5);
	printf("Let's see what's there: %s\n", p_d->key);
	printf("Let's remove this entry. ");
	ba_remove(b, 4, "music", 5);
	printf("The new size of the bucket array is %d.\n", ba_size(b));
	d.key = "hiking";
	d.key_l = 6;
	d.value = 5;
	ba_insert(b, d, 4);
	printf("Let's add a new element, and the new size is %d.\n", ba_size(b));
	p_d = ba_get(b, 4, "hiking", 5);
	printf("The new element is: %s, %d\n", p_d->key, p_d->value);
	d.value = 10;
	ba_set(b, 4, "hiking", 5, d.value);
	p_d = ba_get(b, 4, "hiking", 5);
	printf("Set %s to %d\n", p_d->key, p_d->value); 
	ba_insert(b, d, 20);
	ba_increase(b);
	
}
