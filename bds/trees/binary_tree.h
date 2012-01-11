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
	uint size;
	uint height;
	bt_cursor root;
};

typedef struct bt_node* bt_cursor;

/* Initializes an empty binary tree */
struct bt* bt_init();	
/* Initializes a binary tree and puts data in root */
struct bt* bt_init_value(struct generic_data data);
/* Returns 1 if binary tree is proper, 0 otherwise 
 * proper: each node has zero or two children */
uchar_t bt_isProper(struct bt *t);
/* Returns the height of qNode */
uchar_t bt_height(struct bt_node qNode);
/* Returns the depth of qNode */
uchar_t bt_depth(struct bt_node qNode);
/* Inserts a value in a child node of cur */
void bt_insert(struct bt *t, struct bt_node n, struct generic_data data);
/* Returns 1 if node is internal, else 0 
 * Use !bt_isInternal() to check if a node is external */
uchar_t bt_isInternal(struct bt_node n);
/* Returns the value of the left child of node n */
struct generic_data bt_get_left(struct bt *t, struct bt_node n);
/* Returns the value of the right child node n */
struct generic_data bt_get_right(struct bt *t, struct bt_node n);
/* Returns the value of the parent of node n */
struct generic_data bt_get_parent(struct bt *t, struct bt_node n);
/* Sets the value of the left child to data */
void bt_set_left(struct bt *t, struct bt_node n, struct generic_data data);
/* Sets the value of the right child to data */
void bt_set_right(struct bt *t, struct bt_node n, struct generic_data data);
/* Sets the value of the parent to data */
void bt_set_parent(struct bt *t, struct bt_node n, struct generic_data data);

/* Traverses the tree in order and applies f to every element */
void bt_traversal_in(struct bt *t, void(*f)(struct bt_node));
/* Traverses the tree pre order and applies f to every element */
void bt_traversal_pre(struct bt *t, void(*f)(struct bt_node));
/* Traverses the tree post order and applies f to every element */
void bt_traversal_post(struct bt *t, void(*f)(struct bt_node));

/* These are traversal methods which work with cursors, for subtree traversals
 * f has same meaning as above */
/* Traverses the subtree rooted at node n in order */
void bt_subtr_trav_in(bt_cursor cur, void(*f)(struct bt_node));
/* Traverses the tree pre order and applies f to every element */
void bt_subtr_trav_pre(bt_cursor cur, void(*f)(struct bt_node));
/* Traverses the tree post order and applies f to every element */
void bt_subtr_trav_post(bt_cursor cur, void(*f)(struct bt_node));

/* Adds a subtree as left child on node n, returns if there is a left child */
void bt_add_left(struct bt *t, struct bt_node n, struct bt_node stroot);
/* Adds a subtree as right child on node n, returns if there is a right child */
void bt_add_right(struct bt *t, struct bt_node n, struct bt_node stroot);

#endif
