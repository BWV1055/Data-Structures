/*
 * Implementation of the tree methods
 *
 * 
 *
 *
 *
 */

#include "tree.h"
#include <stdlib.h>
#include <string.h>

/* Returns the number of nodes in the tree */
int tr_size(struct tree *t)
{
	return t->size;
}
/* Returns 1 if the tree has no elements, 0 otherwise */
int tr_isEmpty(struct tree *t)
{
	return (t->size==0);
}
/* Returns a newly created and initialized tree
 * This is the way to use the other functions described here */
struct tree* tr_init()
{
	struct tree_node root;
	root.nr_chd = 0;
	root.parent = NULL;
	memset(root.children, 0, TR_NODE_MAX_CHILDREN*sizeof(struct tree_node*));
	//root.data = 0;
	struct tree *t = malloc(sizeof *t);
	t->size = 0;
	t->depth = 0;
	t->root = root;
	return t;
}

/* Adds a new element in the tree at the position specified by path 
 * If there is already an element at this position, the function returns 
 * To replace a value, use tr_set instead
 * The path starts at the root, the first value shows the root child index */
void tr_insert(struct tree *t, struct generic_data data, struct fpath path)
{
	if(t->size>=TR_MAX_NODES) {
		mds_error(E_MAX_SIZE, "Tree has maximum number of nodes");
		return;
	}

	tr_cursor it = t->root;
	uint i=0;

	while(++i<path.len) {
		if(path.legs[i-1]>=it->nr_chd)
			break;
		it = it->children[path.legs[i-1]];
	}
	if(i!=path.len || it->nr_chd==TR_NODE_MAX_CHILDREN) {
		mds_error(E_ILLEGAL_ARGUMENT, "Non-existent path");
		return;
	}
	struct tr_node *n = malloc(sizeof *n);
	n->nr_chd = 0;
	n->parent = it;
	memset(n->children, 0, TR_NODE_MAX_CHILDREN*sizeof(tr_cursor));
	n->data = data;
	it->children[it->nr_chd] = n;
	it->nr_chd++;
	t->size++;
}

/* Inserts value d in the root, or replaces the current value */
void tr_insert_root(struct tree *t, struct generic_data d)
{
	t->root.data = d;
	if(t->size==0)
		t->size++;
}
/* Removes the element found at the path path and returns it
 *  */
struct generic_data tr_remove_path(struct tree *t, int *path, int path_len)
{
	struct generic_data d;
	return d;
}
/* Removes first occurence of data d in a breath first walk */
char* tr_remove_data(struct tree *t, struct generic_data d)
{
	char *c = '\0';
	return c;
}

void traverse_pre(tr_cursor it, void(*f)(struct tr_node))
{
	uint it_chd = it->nr_chd;
	while(it_chd--) {
		f(*it->children[it_chd]);
		traverse_pre(it->children[it_chd], f);
	}
}
/* Traverses the tree preorder and applies function f to every element 
 * Sequential traversal of a document */
void tr_traverse_pre(struct tree *t, void(*f)(struct tr_node))
{
	f(*t->root);
	traverse_pre(t->root, f);
}

void traverse_post(tr_cursor it, void(*f)(struct tr_node))
{
	uint it_chd = it->nr_chd;
	while(it_chd--) {
		traverse_post(it->children[it_chd], f);
		f(*it->children[it_chd]);
	}
}
/* Traverses the tree postorder and applies function f to every element 
 * Determine the size of a folder with files and folders */
void tr_traverse_post(struct tree *t, void(*f)(struct tr_node))
{
	traverse_post(t->root, f);
	f(*t->root);
}

void traverse_level(tr_cursor it, void(*f)(struct tr_node))
{
	uint it_chd;
	for(it_chd=0;it_chd<it->nr_chd;it_chd++) 
		f(*it->children[it_chd]);
	for(it_chd=0;it_chd<it->nr_chd;it_chd++)
		traverse_level(it->children[it_chd], f);
}
/* Visits all the nodes at level l, then continues with nodes at level l+1 */ 	
void tr_traverse_level(struct tree *t, void(*f)(struct tr_node))
{
	f(*t->root);
	traverse_level(t->root);
}

tr_cursor* tr_children(tr_cursor cur)
{
	return n->children;
}

uint tr_height(struct tree *t, tr_cursor cur)
{
	uint h = 0, chd_it;
	if(tr_leaf(t, *cur))
		return 0;
	chd_it = cur->nr_chd;
	while(chd_it--)
		h = MAX(h, tr_height(t, cur->children[chd_it]));
	return h+1;
}

uint tr_depth(struct tree *t, tr_cursor cur)
{
	if(cur->parent==NULL)
		return 0;
	return tr_depth(t, cur->parent)+1;
}
