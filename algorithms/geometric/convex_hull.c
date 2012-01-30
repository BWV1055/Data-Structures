/*
 *	Determine the convex hull of a set of points
 *		The points are in the plane
 */

struct point {
	int x;
	int y;
};

typedef point p2d_t;

/* positive, pj is left of [pi, pk] */
float direction(p2d_t pi, p2d_t pj, p2d_t pk) {
	return (pj.x-pi.x)*(pk.y-pi.y) - (pk.x-pi.x)*(pj.y-pi.y);
}
/* Returns 1 if pk, known to be colinear with pi and pj, is actually on the segment [pi...[j] */
char on_segment(p2d_t pi, p2d_t pj, p2d_t pk) {
	if(min(pi.x, pj.x)<=pk.x<=max(pi.x, pj.x) &&
	   min(pi.y, pj.y)<=pk.y<=max(pi.y, pj.y))
		return 1;
	return 0;
}
/* Return 1 if [p1, p2] intersects [p3, p4] */
char intersection(p2d_t p1, p2d_t p2, p2d_t p3, p2d_t p4) {
	float d1 = direction(p3, p4, p1);
	float d2 = direction(p3, p4, p2);
	float d3 = direction(p1, p2, p3);
	float d4 = direction(p1, p2, p4);
	if((d1>0 && d2<0) ||
	   (d1<0 && d2>0) ||
	   (d3>0 && d4<0) ||
	   (d3<0 && d4>0))
		return 1;
	if(d1==0 && on_segment(p3, p4, p1))
		return 1;
	if(d2==0 && on_segment(p3, p4, p2))
		return 1;
	if(d3==0 && on_segment(p1, p2, p3))
		return 1;
	if(d4==0 && on_segment(p1, p2, p4))
		return 1;
	return 0;
}
/* Sort points[p...r] by the polar angle made with origin p0 */
p2d_t* polar_angle_sort(p2d_t* p0, p2d_t* points, int p, int r) {
	int i, j, k;
	int piv; 
	if(r-p<=1)
		return;
	p2d_t* g = malloc((r-p+1)*sizeof(*g));
	p2d_t* l = malloc((r-p+1)*sizeof(*l));
	float v1 = direction(p0, points[p], points[floor(p+r)/2])
	float v2 = direction(p0, points[floor(p+r)/2], points[r]);
	float v3 = direction(p0, points[p], points[r]);
	piv = v1>v2?(v2>v3?p:r):(v2>v3?floor(p+r)/2:r);
	val_piv = points[piv];
	for(i=p;i<=r;i++) {
		if(i==piv)
			continue;
		if(direction(p0, val_piv, points[i])>0)
			l[j++] = points[i];
		else
			g[k++] = points[i];
	}
	l = polar_angle_sort(p0, l, 0, j);
	g = polar_angle_sort(p0, g, 0, r);
	for(i=0;i<j;i++)
		points[i] = l[i];
	points[i] = val_piv;
	for(i=0;i<k;i++)
		points[j+i] = g[i];
	return points;
}

void convex_hull(p2d_t* points, int n, p2d_t* hull, int* hull_size) {
	int i;
	int min_y = 100, min_pos=0;
	for(i=0;i<n;i++)
		if(points[i].y<min_y) {
			min_y = points[i].y;
			min_pos = i;
		}
	p2d_t p0 = points[min_pos];
	for(i=min_pos;i<n-1;i++)
		points[i] = points[i+1];
	n--;
	points = polar_angle_sort(p0, points, 0, n);
	p_stack_t* qPoints = s_init();
	push(qPoints, p0);
	push(qPoints, points[0]);
	push(qPoints, points[1]);
	for(i=2;i<n;i++) {
		while(direction(next_to_top(qPoints), top(qPoints), points[i])<0)
			pop(qPoints);
		push(qPoints, points[i]);
	}
	p2d_t* point;
	*hull_size = 0;
	while(point = pop(qPoints))
		hull[hull_size++] = *point;
}



/* Stack of points */
struct p_node {
	p2d_t point;
	p_node* next;
};

typedef struct p_node p_node_t;

struct stack {
	int size;
	p_node_t* top;
	p_node_t* bottom;
};

typedef struct stack p_stack_t;

p_stack_t* s_init() {
	p_stack_t* newStack = malloc(sizeof(*newStack));
	newStack->top = newStack->bottom = NULL;
	newStack->size = 0;
	return newStack;
}	

p2d_t* pop(p_stack_t* stack) {
	if(!stack->size)
		return NULL;
	p_node* temp = stack->top;
	p2d_t* toReturn = malloc(sizeof(*toReturn));
	*toReturn = stack->top->point;
	stack->top = stack->top->next;
	free(temp);
	stack->size--;
	return toReturn;
}

void push(p_stack_t* stack, p2d_t point) {
	p_node_t* temp;
	if(stack->top) {
		temp = stack->top;
		stack->top = malloc(sizeof(p_node_t));
		stack->top->point = point;
		stack->top->next = temp;
	} else {
		stack->top = stack->bottom = malloc(sizeof(p_node_t));
		stack->top->next = NULL;
		stack->top->point = point;
	}
	stack->size++;
}

p2d_t* top(p_stack_t* stack) {
	if(!stack->size)
		return NULL;
	return &stack->top->point;
}

p2d_t* next_to_top(p_stack_t* stack) {
	if(stack->size<2)
		return NULL;
	return &stack->top->next->point;
}
