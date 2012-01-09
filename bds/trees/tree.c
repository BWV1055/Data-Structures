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
void tr_insert(struct tree *t, struct generic_data d, int *path, int path_len)
{
	if(t->size>=TR_MAX_NODES)
		return;

	struct tree_node *it = &t->root;
	int i=0;

	while(++i<path_len) {
		if(path[i-1]==it->nr_chd)
			break;
	    if(path[i-1]<it->nr_chd)
			it = it->children[path[i-1]];
	}
	if(i!=path_len || it->nr_chd==TR_NODE_MAX_CHILDREN)
		return;
	/* The iterator now points to the parent */
	struct tree_node *new = malloc(sizeof *new);
	new->nr_chd = 0;
	new->parent = it;
	memset(new->children, 0, TR_NODE_MAX_CHILDREN*sizeof(struct tree_node*));
	new->data = d;
	it->children[it->nr_chd] = new;
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
/* Not part of the interface, used in tr_walk_bf */
void walk_bf(struct tree_node *it, void(*f)(struct tree_node))
{
	int i;
	if(it->nr_chd) {
		for(i=0;i<it->nr_chd;i++)
			f(*it->children[i]);
		for(i=0;i<it->nr_chd;i++)
			walk_bf(it->children[i], f);
	}
}
/* Walks the tree breath first and applies function f to every element */
void tr_walk_bf(struct tree *t, void(*f)(struct tree_node))
{
	f(t->root);
	walk_bf(&t->root, f);
}
/* Not part of the interface, used in tr_walk_df */
void walk_df(tree_node *it, void(*f)(struct tree_node))
{
	int i;
	if(it->nr_chd) {
		for(i=0;i<it->nr_chd;i++)
			walk_df(it->children[i], f);
		for(i=0;i<it->nr_chd;i++)
			f(*it->children[i]);
	}
}
/* Walks the tree depth first and applies function f to every element */
void tr_walk_df(struct tree *t, void(*f)(struct generic_data))
{
	walk_df(&t->root, f);
	f(t->root);
}

struct tree_node** tr_children(struct tree_node *n)
{
	return n->children;
}

int tr_height(struct tree *t, struct tree_node *n)
{
	int h = 0, chd_it;
	if(n->nr_chd) {
		chd_it = n->nr_chd;
		while(chd_it--)
			h = MAX(h, tr_height(t, n->children[chd_it]));
		return h+1;
	} else
		return tr_height_n(t, n);
}

int tr_height_n(struct tree *t, struct tree_node *n)
{
	if(n == &t->root) return 0;
	return tr_height_n(t, n->parent);
}

