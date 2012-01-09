/*
 *
 *
 *
 *
 */

#include "tree.h"
#include <stdio.h>

void print_data(struct tree_node n)
{
	printf("Node value: %d\n", n.data.val);
}

int main()
{
	int path[TR_MAX_DEPTH];
	struct tree *t = tr_init();
	struct generic_data d;

	d.val = 1;
	tr_insert_root(t, d);

	d.val = 2;
	path[0] = 1;
	tr_insert(t, d, path, 1);
		
	d.val = 3;
	path[0] = 0;
	tr_insert(t, d, path, 1);

	d.val = 4;
	path[0] = 0;
	path[1] = 1;
	tr_insert(t, d, path, 2);

	d.val = 5;
	path[0] = 0;
	path[1] = 1;
	path[2] = 1;
	tr_insert(t, d, path, 3);

	//tr_walk_df(t, print_data);
	tr_walk_bf(t, print_data);
	printf("Tree height: %d\n", tr_height(t, &t->root));

}
