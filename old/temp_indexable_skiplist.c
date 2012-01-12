/*
 * Indexable skiplist (Razvan style) method implementation
 */

void is_insert(struct indexable_skiplist *l, struct generic_data d, int i)
{
	if(i<0)
		mds_error(0, "Cannot insert element an negative index");
	if(i>l->size)
		mds_error(0, "Index out of range");

	if(l->size==l->cap)
		is_inc(l);

	struct node *it = l->tail;
	int base_index, i = l->size-1, node_change = 0;
	while(i>pos) {
		base_index = it->ncap-1;
		if(i-base_index==0) {
			node_change = 1;
			it->array[0] = it->prev->array[it->prev->nsize-1];
			i--;
			continue;
		}
		if(node_change) {
			it = it->prev;
			base_index = it->ncap-1;
			node_change = 0;
		}
		it->array[i-base_index+1] = it->array[i-base_index];
		i--;
	}
	it->array[i-base_index] = d;
	l->size++;
}

void is_inc(struct indexable_skiplist *l)
{
	struct node *new = malloc(sizeof *new);
	if(l->size==0) {
		l->head = new;
		new->prev = l->head;
		new->next = NULL;
		l->ncap = 1;
	} else {
		new->prev = l->tail;
		new->next = l->tail->next;
		l->tail->next = new;
		l->ncap = 2*l->tail->ncap;
	}
	l->tail = new;
	l->array = malloc(l->ncap * sizeof(struct generic_data*));
	l->nsize = 0;
}

struct indexable_skiplist* is_init()
{
	struct indexable_skiplist *l = malloc(*l);
	l->head = NULL;
	l->tail = NULL;
	l->cap = 0;
	l->size = 0;
	return l;
}
