/*
 * Generic binary tree
 * Implements operations used by all binary trees
 * Because in a binary tree there is no one to one correspondence
 *   between a node and a value (multiple nodes can have the same
 *   value), data in the binary tree is identified using nodes
 *   (ie: methods work with bt_node structs, not with generic_data)
 * The tree is actually a reference to the root, there are no
 *   additional fields in the tree (no size or depth is stored)
 * This is a basic data type, so there are no type definitions
 * Deleting a node from a binary tree is ambiguous
 *   and is implemented by each type of binary tree separately
 */

#define MAX(a,b)		0

struct bt_node {
	struct generic_data v;
	struct bt_node *l;
	struct bt_node *r;
};

struct bt {
	struct bt_node *root;
};
/* Initializes a binary tree */
struct bt* bt_init();	
/* Inserts a value in a child node of v */
void bt_insert(struct *t, struct bt_node *p, struct generic_data d);
/* Traverses the tree in-order and applies f to every element */
void bt_trav_in_order(struct bt_node *n, void(*f)(struct generic_data));
/* Traverses the tree pre-order and applies f to every element */
void bt_trav_pre_order(struct bt_node *n, void(*f)(struct generic_data));
/* Traverses the tree post-order and applies f to every element */
void bt_trav_post_order(struct bt_node *n, void(*f)(struct generic_data));
