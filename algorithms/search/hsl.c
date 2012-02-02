/*
 *	Locality sensitive hashing 
 */

#include "math.h"
#include "stdio.h"

struct _object {
	/* Number of dimension, greater than 20 up to thousands */
	int n_dim;
	/* A total of n_dim*sizeof(int)*8 bits */
	int* values;
};

typedef struct _object object;
/* Translate origin and multiply by a large integer to get only positive integer coordinates */
int distance(object* o1, object* o2) {
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
/* Returns the number of objects within distance r from q 
 * The results are in res */
int ball(object* q, int r, object* set, int n, object* res) {


}

int hamm_distance(object* o1, object* o2) {
	int i, p = o1->n_dim, dist = 0;
	for(i=0;i<p;i++)
		if(o1->values[i] != o2->values[i])
			dist++;
	return dist;
}
/* TODO: add hash functions for this measure */
float dot_p_distance(object* o1, object* o2) {
	float dist;
	int i;
	for(i=0;i<o1->n_dim;i++)
		dist += o1->values[i] * o2->values[i];
	return dist;
}

struct h_table {
	/* Number of buckets, same as set size */
	int m;
	lln** roots;
}

struct h_table* ht_init(int m) {
	struct h_table* ht = malloc(sizeof(*ht));
	ht->m = m;
	ht->roots = malloc(m*sizeof(*ht->roots));
	return ht;
}
/* Concatenate all ints of an object, create a string of bits, check if bits[pos] is 1 or 0 
 * Pr[hash(u, rand_pos)=hash(v, rand_pos)] ~ cos(u,v) */
char hash(object* o, int pos) {
	int dim = floor(pos/(8*sizeof(int)));
	pos %= 8*sizeof(int);
	return ((o->values[dim]>>pos)%2)*2-1;
}

int g(object* o, int index, int* H, int k) {
	int i, res = 0;
	char bit;
	for(i=0;i<k;i++) {
		bit = hash(o, H[index*k+i]);
		res = res<<1;
		res += bit;
	}
	return res;
}

int second_level_map(struct h_table* ht, int v, int k) {
	
	
}

typedef char (*hash_f) (object*, int);

void preprocess(object* set, int n) {
	int i, l;
	int m, b;
	int k;
	/* l hash functions */
	int* H = malloc(l*k*sizeof(int));
	for(i=0;i<l;i++)
		for(j=0;j<k;j++)
			H[i*k+j] = rand();


}
/* Nearest neighbor */
object* nns(object* q, object* set, int n) {



	free(h_tables);
}
/* Return a point p so that distance(p,q)<= (1+eps) distance(nn(q),q) */
object* eps_nns(object* q, float eps, object* set, int n) {

}




/* Res keeps an index of objects in set arranged by distance to q 
 * res[0] is the closest object to q, res[n-1] the farthest */
// O(d*n^(1/1+eps))
void search(object q, object* set, object* res, int n) {
	
}

#define MAX_DIM	100
#define MAX_SET	2000

int dset[MAX_SET][MAX_DIM];

int main(int argv, char** argc) {
	
	int n_dim, n_elem;
	void* next_line;
   	next_line = malloc(MAX_DIM*sizeof(int));
	char* filename = malloc(40*sizeof(char));
	FILE* datafile = NULL;
	printf("Please give the file location for the data: ");
	scanf("%s", filename);
	datafile = fopen(filename, "r");
	while(!datafile) {
		printf("Could not open file %s", filename);
		printf("Please give the file location for the data: ");
		scanf("%s", filename);
		datafile = fopen(filename, "r");
	}
	free(filename);
	next_line = (char*) next_line;
	n_dim = fgetc(datafile);
	n_elem = fgetc(datafile);
	for(i=0;i<n_elem;i++) {
		next_line = (char*)next_line;
		next_line = fgets(next_line, 100, datafile);
		next_line = (int*)next_line;
		for(j=0;j<n_dim;j++)
			dset[i][j] = next_line[j];
	}
}
