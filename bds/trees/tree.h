/*
 * Generic specification for a tree data structure
 * This is an ordered tree
 * 
 * All the methods should work with values, not with references
 * This is because returning references allows someone to use tamper the tree
 * The problem with tree values is more subtle:
 * 	There can be multiple nodes with the same value and it's difficult to specify
 * 	a node based on the value
 * So tree methods work with nodes, and sometimes with pointers to nodes 
 *
 * The update methods provided here are generic
 * For different types of trees/applications, additional update methods are available
 *
 */

#ifndef _TREE_H_
#define _TRRE_H_

#include <stdio.h>
#include "../mds/mds_data_types.h"

#define TR_NODE_MAX_CHILDREN 		8
#define TR_MAX_NODES		 		4096
#define TR_MAX_DEPTH		 		128

/* Path type */
typedef uchar[TR_MAX_DEPTH] legs_t;
/* Full path */
struct fpath {
	legs_t legs;
	size_t len;
};

struct tr_node {
	int n_chd;
	struct generic_data data;
	struct tr_node *parent;
	struct tr_node **children;
};

struct tree {
	struct tr_node *root;
	int size;
	int depth;
};

typedef struct tr_node* tr_cursor;

/* Returns the number of nodes in the tree */
size_t tr_size(struct tree *t);
/* Returns 1 if the tree has no elements, 0 otherwise */
uchar tr_isEmpty(struct tree *t);
/* Returns a newly created and initialized tree
 * This is the way to use the other functions described here */
struct tree* tr_init();
/* Initialize tree with a value */
struct tree* tr_init_data(struct generic_data data);
/* Adds a new element in the tree at the position specified by path 
 * If there is already an element at this position, the function returns */
void tr_insert(struct tree *t, struct generic_data data, struct fpath path);
/* Replaces the element present at path and returns it */
struct generic_data tr_replace(struct tree *t, struct fpath path, struct generic_data replace);
/* Removes the element found at the fpath path, if the path exists 
 * and returns it */
struct generic_data tr_remove_path(struct tree *t, struct fpath path);
/* Removes first occurence of data in a breath first traversal */
char* tr_remove_data(struct tree *t, struct generic_data data);
/* Returns the root */
tr_cursor tr_root(struct tree *t);
/* Returns a list of the children of the selected node */
tr_cursor* tr_children(tr_cursor cur);
/* Returns the parent */
tr_cursor tr_parent(tr_cursor cur);
/* Return 1 if node if leaf, 0 otherwise */
uchar tr_leaf(struct tree *t, struct tr_node node);
/* Returns an array with all siblings */
struct generic_data* tr_siblings(struct tree *t, struct fpath path);

/* Traverses the tree breath first and applies function f to every element 
 * f can do many more things if it works with the actual node, and not with the data in it */
void tr_traverse_bf(struct tree *t, void (*f)(struct tr_node));
/* Traverses the tree depth first and applies function f to every element */
void tr_traverse_df(struct tree *t, void (*f)(struct tr_node));

/* Returns the height of a sub-tree in O(n) */
uint tr_height(struct tree *t, tr_cursor cur);
/* Returns the depth of a sub-tree */
uint tr_depth(struct tree *t, tr_cursor cur);
/* Takes a path and returns a cursor */
tr_cursor tr_path_to_cur(struct tree *t, struct fpath path);
/* Removes a subtree pointed by cur, returns the parent of cur */
tr_cursor tr_remove_subtr(struct tree *t, tr_cursor cur);
/* Adds a subtree to_add on the next available position as a child of cur 
 * Returns NULL if the operation failed, or to_add on success */
tr_cursor tr_add_subtr(struct tree *t, tr_cursor to_add, tr_cursor cur);

#endif
