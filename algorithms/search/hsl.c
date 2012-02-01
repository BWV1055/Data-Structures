/*
 *	Locality sensitive hashing 
 */

#include "math.h"

struct _object {
	/* Number of dimension, greater than 20 up to thousands */
	int n_dim;
	int* values;
};

typedef struct _object object;
/* Translate origin and multiply by a large integer to get only positive integer coordinates */
int distance(object o1, object o2) {
	float sq_dist = 0;
	int i, p;
	/*
	 * p = o1->n_dim;
	 */
	/* l2 applied to translations and random rotations of data
	 * produces almost same results as l1 
	 * See http://archive.numdam.org/ARCHIVE/SAF/SAF_1975-1976___/SAF_1975-1976____A15_0/SAF_1975-1976____A15_0.pdf */
	p = 1;
	for(i=0;i<p;i++)
		sq_dist += (o1->values[i] - o2->values[i])^p;
	return pow(1/p, sq_dist);
}

int hamm_distance(object o1, object o2) {
	int i, p = o1->n_dim, dist = 0;
	for(i=0;i<p;i++)
		if(o1->values[i] != o2->values[i])
			dist++;
	return dist;
}
/* TODO: add hash functions for this measure */
float dot_p_distance(object o1, object o2) {
	float dist;
	int i;
	for(i=0;i<o1->n_dim;i++)
		dist += o1->values[i] * o2->values[i];
	return dist;
}

struct h_table {
	/* Number of buckets */
	int m;
	lln** roots;
}

int hash(object* o, int i) {
	
	
}
/* Nearest neighbor */
object* nns(object* q, object* set, int n) {

}
/* Return a point p so that distance(p,q)<= (1+eps) distance(nn(q),q) */
object* eps_nns(object* q, float eps, object* set, int n) {

}




/* Res keeps an index of objects in set arranged by distance to q 
 * res[0] is the closest object to q, res[n-1] the farthest */
// O(d*n^(1/1+eps))
void search(object q, object* set, object* res, int n) {
	
}
