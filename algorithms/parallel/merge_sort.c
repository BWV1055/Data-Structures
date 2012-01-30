/*
 *	Parallel implementation for merge sort, in Cilk
 *	Parallelizing merge_sort is straightforward:
 *		spawn another child for merge_sort(v, p, m) and let the original
 *		process do merge_sort(v, m+1, q)
 *	To parallelize merge, pick the middle element (mid) of the larger vector
 *		and search its position in the smaller one (use binary search to find
 *		the position because it is sorted).
 *	Put mid where it belongs in the merged vector, then merge the two vectors with
 *		elements smaller than mid, and the two vectors with elements larger than mid,
 *		and place them before and after mid. See "Introduction to Algorithms", ch. 27.3
 *
 */

void merge_sort(int* v, int p, int r) {
	if(r<=p)
		return;
	int q = floor((p+r)/2);
	merge_sort(v, p, q);
	merge_sort(v, q+1, r);
	merge(v, p, q, r);
}

void merge(int* v, int p, int q, int r) {
	int i=0, j=0, k=0;
	int l1 = q-p+1;
	int l2 = r-q;
	int* a = malloc((p-r+1)*sizeof(int));
	for( ;i<l1 || j<l2; ) {
		if(v[p+i]>v[q+1+j])
			a[k++] = v[q+1+j++];
		else
			a[k++] = v[p+i++];
	}
	if(i==l1) {
		while(j<l2)
			a[k++] = v[q+1+j++];
	} else if(j==l2) {
		while(i<l1)
			a[k++] = v[p+i++];
	}
	return a;
}

/* Sort A[p..r] and put it in B[s..s+r-p] */
cilk void p_merge_sort(int* A, int p, int r, int* B, int s) {
	int n = r-p+1;
	if(n==1) {
		B[s] = A[p];
		return;
	}
	int q = floor((p+r)/2);
	int q_p = q-p+1;
	int* T = malloc(n*sizeof(int));
	spawn p_merge_sort(A, p, q, T, 0);
	p_merge_sort(A, q+1, r, T, q_p);
	sync;
	p_merge(T, 0, q_p-1, q_p, n-1, B, s);
}

/* the first interval is larger than the second */
cilk p_merge(int* T, int p1, int r1, int p2, int r2, int* A, int p3) {
	int n1 = r1-p1+1;
	int n2 = r2-p2+1;
	int swap;
	if(n1<n2) {
		swap = p1; p1 = p2; p2 = swap;
		swap = r1; r1 = r2; r2 = swap;
		swap = n1; n1 = n2; n2 = swap;
	}
	if(n1==0) 
		return;
	int q1 = floor((p1+r1)/2);
	int q2 = binary_search(T[q1], T, p2, r2);
	int q3 = p3+(q1-p1)+(q2-p2);
	A[q3] = T[q1];
	spawn p_merge(T, p1, q1-1, p2, q2-1, A, p3);
	p_merge(T, q1+1, r1, q2, r2, A, q3+1);
	sync;
}

int binay_search(int x, int* T, int p, int r) {
	int low = p;
	int high = max(p, r+1);
	int mid;
	while(low<high) {
		mid = floor((low+high)/2);
		if(x<=T[mid])
			high = mid;
		else
			low = mid+1;
	}
	return high;
}	

