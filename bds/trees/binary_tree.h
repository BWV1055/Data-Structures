/*
 * Generic binary tree
 *	Many methods are wrappers for similar methods in the tree ADT
 *
 * Deleting a node from a binary tree is ambiguous
 *   and is implemented by each type of binary tree separately
 *
 *
 *
 *
 */

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "../../mds/mds_errors.h"
#include "../../mds/mds_data_types.h"

#define MAX(a,b)		0

struct bt_node {
	struct generic_data data;
	struct bt_node *parent;
	struct bt_node *left;
	struct bt_node *right;
	uchar_t flags;
};

struct bt {
	size_t size;
	uint_t height;
	bt_cursor root;
};

typedef struct bt_node* bt_cursor;

/* Initializes a binary tree with data placed in the root */
struct bt* bt_init(struct generic_data data);	
/* Returns 1 if binary tree is proper, 0 otherwise 
 * proper: each node has zero or two children */
uchar_t bt_isProper(struct bt *t);
/* Returns the height of qNode in O(n) time */
uchar_t bt_height(struct bt_node qNode);
/* Returns the depth of qNode in O(n) time */
uchar_t bt_depth(struct bt_node qNode);
/* Tries to insert data in the left child node, then right child node
 * Returns a cursor to the newly created node or NULL if it fails 
 * This is like calling bt_set_left and bt_set_right, except no new node is created */
bt_cursor bt_insert(struct bt_node n, struct generic_data data);
/* Returns 1 if node is internal (has at least one child), else 0 
 * Use !bt_isInternal() to check if a node is external */
uchar_t bt_isInternal(struct bt_node n);
/* Returns the value of the left child of node n, or NULL if there is no left child */
struct generic_data* bt_get_left(struct bt_node n);
/* Returns the value of the right child node n, or NULL if there is no right child */
struct generic_data* bt_get_right(struct bt_node n);
/* Returns the value of the parent of node n, or NULL if there is no parent */
struct generic_data* bt_get_parent(struct bt_node n);
/* Sets the value of the left child to data, adds a new left child node if there isn't one */
void bt_set_left(struct bt_node n, struct generic_data data);
/* Sets the value of the right child to data, adds a new right child node if there isn't one */
void bt_set_right(struct bt_node n, struct generic_data data);
/* Sets the value of the parent to data, if parent exists (the root has no parent) */
void bt_set_parent(struct bt_node n, struct generic_data data);

/* Traverses the tree in order and applies f to every element */
void bt_traversal_in(struct bt *t, (void*)(*f)(struct bt_node));
/* Traverses the tree pre order and applies f to every element */
void bt_traversal_pre(struct bt *t, (void*)(*f)(struct bt_node));
/* Traverses the tree post order and applies f to every element */
void bt_traversal_post(struct bt *t, (void*)(*f)(struct bt_node));

/* These are traversal methods which work with cursors, for subtree traversals
 * f has same meaning as above */
/* Traverses the subtree rooted at node n in order */
void bt_subtr_trav_in(struct bt_node n, void(*f)(struct bt_node));
/* Traverses the tree pre order and applies f to every element */
void bt_subtr_trav_pre(struct bt_node n, void(*f)(struct bt_node));
/* Traverses the tree post order and applies f to every element */
void bt_subtr_trav_post(struct bt_node n, void(*f)(struct bt_node));

/* Adds a subtree as left child on node n, returns if there is a left child */
void bt_add_left(struct bt *t, struct bt_node n, struct bt_node stroot);
/* Adds a subtree as right child on node n, returns if there is a right child */
void bt_add_right(struct bt *t, struct bt_node n, struct bt_node stroot);

/* Removes the left subtree of n */
void bt_remove_left(struct bt_node n);
/* Removes the right subtree of n */
void bt_remove_right(struct bt_node n);

/* Reads tree data from file f and creates a binary tree based on this data
 * See tr_read_file() description in tree.h for the format of the file */
struct bt* bt_read_file(FILE *f);
/* Writes tree t data to file f 
 * See above */
void bt_write_file(struct bt *t, FILE *f);

#endif
