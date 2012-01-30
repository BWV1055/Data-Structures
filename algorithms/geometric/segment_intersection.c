/*
 *	Determine if any two segments intersect
 *	Use a line which sweeps the x axis and stops at positions where a segment starts/ends
 */

struct line {
	p2d_t start;
	p2d_t end;
};

typedef struct line seg2d_t;

float cross_product(seg2d_t s1, seg2d_t s2) {
	p2d_t endTran;
	endTran.x = s2.start.x - (s1.end.x-s2.end.x);
	endTran.y = s2.start.y - (s1.end.y-s2.end.y);
	return direction(s1.start, s1.end, endTran);
}

char segment_intersection(seg2d_t* segments, int num) {

}

/* RBT to keep the segments ordered by their value at x */

struct seg_n {
	seg2d_t segment;
	seg_n* left;
	seg_n* right;
	seg_n* parent;
	char color;
};

#define BLACK 0
#define RED 1

struct seg_rbt {
	seg_n* root;
	int size;
	int height;
};

seg_rbt* t_init() {
	seg_rbt* newRbt = malloc(sizeof(*newRbt));
	newRbt->root = NULL;
	newRbt->size = 0;
	newRbt->height = 0;
	return newRbt;
}

segment* t_search(seg_n* cur, seg2d_t qSeg) {
	if(t->size==0)
		return NULL;
	float cp = cross_product(cur->segment, qSeg);
	if(cp==0)
		return cur->segment;
	if(cp>0)
		return t_search(cur->left, qSeg);
	else
		return t_search(cur->right, qSeg);
}

void t_insert(seg_rbt* t, segment* s);
void t_delete(seg_rbt* t, float angle);
