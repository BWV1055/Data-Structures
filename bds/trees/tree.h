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
 *
 * Note on tr_cursor:
 * 	tr_cursor is used ONLY when there is no other option left (for example, when a method
 * 	has to return NULL), otherwise, passing a tr_node (or path) (and possibly the actual tree) is 
 * 	the preferred way of defining a function.
 *
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include "../../mds/mds_data_types.h"

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
/* Returns all the entries in the tree, use tr_size()
 * for the number of elements */
struct generic_data* tr_entries(struct tree *t);
/* Adds a new element in the tree at the position specified by path 
 * If there is already an element at this position, the function returns */
void tr_insert(struct tree *t, struct generic_data data, struct fpath path);
/* Replaces the data present at path with replace and returns the old value */
struct generic_data tr_replace(struct tree *t, struct fpath path, struct generic_data replace);
/* Removes the element found at the fpath path, if the path exists 
 * and returns it */
struct generic_data tr_remove_path(struct tree *t, struct fpath path);
/* Removes first occurence of data in a breath first traversal */
char* tr_remove_data(struct tree *t, struct generic_data data);
/* Takes a path and returns a cursor */
tr_cursor tr_path_to_cur(struct tree *t, struct fpath path);
/* Takes a cursor and returns a path */
struct fpath* tr_path_to_cur(tr_cursor cur);
/* Returns the root */
tr_cursor tr_root(struct tree *t);
/* Returns a list of the children of the selected node */
tr_cursor* tr_children(tr_cursor cur);
/* Returns the parent */
tr_cursor tr_parent(tr_cursor cur);
/* Return 1 if node is external, 0 otherwise */
uchar_t tr_leaf(struct tr_node node);
/* Returns all the siblings of the node found at path, len is the number of siblings */
void tr_siblings(struct tree *t, struct fpath path, struct generic_data *siblings, size_t *len);

/* Traversing is done in linear time,
 * f can do more things if it works with the actual node */
void tr_trav_pre(struct tree *t, void (*f)(struct tr_node));
void tr_trav_post(struct tree *t, void (*f)(struct tr_node));
/* Visits all the nodes at level l, then continues with nodes at level l+1 */
void tr_trav_level(struct tree *t, void (*f)(struct tr_node));

/* Traversing is done on a subtree rooted at cur */
void tr_subtr_trav_pre(tr_cursor cur, void (*f)(struct tr_node));
void tr_subtr_trav_post(tr_cursor cur, void (*f)(struct tr_node));
void tr_subtr_trav_level(tr_cursor cur, void (*f)(struct tr_node));

/* Returns the height of node qNode in O(n) */
uchar_t tr_height(struct tr_node qNode);
/* Returns the depth of node qNode in O(n) */
uchar_t tr_depth(struct tr_node qNode);
/* Removes a subtree rooted at qNode, returns a cursor at the parent of qNode */
tr_cursor tr_remove_subtr(struct tree *t, struct tr_node qNode);
/* Adds a subtree subTree on the next available position as a child of qNode 
 * Returns NULL if the operation failed, or a cursor to the newly create child of qNode */
tr_cursor tr_add_subtr(struct tree *t, struct tr_node qNode, struct tr_node subTree);


/* Reads tree data from file f and creates a tree based on this data 
 * Data in the file should be structured as follows:
 * 	First line should contain the maximum number of children of a node (eg: 2 for binary)
 *	The rest of the lines should contain pairs of key-value, one on each line
 *	The root should be the first in this set of lines, and the next lines should contain 
 * 	key-value pairs for the children of the root, then key-value pairs for the first child,
 *	and so on.
 *	If there is no child at a certain position, the coresponding line should be left empty.
 * See tree_example.txt for an example (line numbers should be turned on for large files)
 *  */
struct tree* tr_read_file(FILE *f);
/* Writes tree t to file f 
 * The format of the file is similar to the description above */
void tr_write_file(struct tree *t, FILE *f);

#endif
