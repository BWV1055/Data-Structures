/*
 * Generic specification for a tree data structure
 * This is an ordered tree
 * 
 * All the methods should work with values, not with references
 * This is because returning references allows someone to use tamper the tree
 * The problem with tree values is more subtle:
 * 	There can be multiple nodes with the same value and it's difficult to specify
 * 	a node based on the value
 * So tree methods work with nodes 
 *
 * The update methods provided here are generic
 * For different types of trees/applications, additional update methods can be used
 *
 */

#include <stdio.h>

#define TR_NODE_MAX_CHILDREN 8
#define TR_MAX_NODES		 4096
#define TR_MAX_DEPTH		 128
#define MAX(a,b)			 (a)>(b)?(a):(b)

/* Path type
 * typedef unsigned char[TR_MAX_DEPTH] path; */

struct generic_data {
	int val;
};

struct tree_node {
	int nr_chd;
	struct generic_data data;
	struct tree_node *parent;
	struct tree_node *children[TR_NODE_MAX_CHILDREN];
};

struct tree_actual {
	struct tree_node *root;
};

/* Used to keep statistics about a tree
 * */
struct tree {
	int size;
	int depth;
	struct tree_node root;
};
/* Returns the number of nodes in the tree */
int tr_size(struct tree *t);
/* Returns 1 if the tree has no elements, 0 otherwise */
int tr_isEmpty(struct tree *t);
/* Returns a newly created and initialized tree
 * This is the way to use the other functions described here */
struct tree* tr_init();

/* Adds a new element in the tree at the position specified by path 
 * If there is already an element at this position, the function returns */
void tr_insert(struct tree *t, struct generic_data d, int *path, int path_len);
/* Removes the element found at the path path and returns it
 *  */
struct generic_data tr_remove_path(struct tree *t, int *path, int path_len);
/* Removes first occurence of data d in a breath first walk */
char* tr_remove_data(struct tree *t, struct generic_data d);
/* --- Accessor methods */
/* Returns the root */
struct tree_node* tr_root(struct tree_node *t);
/* Returns a list of the children */
struct tree_node** tr_children(struct tree_node *t);
/* Returns the parent */
struct generic_data tr_parent(struct tree_node *t);

/* Walks the tree breath first and applies function f to every element */
void tr_walk_bf(struct tree *t, void(*f)(struct tree_node));
/* Walks the tree depth first and applies function f to every element */
void tr_walk_df(struct tree *t, void(*f)(struct generic_data));
/* Returns an array with all siblings */
struct generic_data* tr_siblings(struct tree *t, int *path, int path_len);

/* Returns the height of a tree in O(n) */
int tr_height(struct tree*t, struct tree_node *n);
