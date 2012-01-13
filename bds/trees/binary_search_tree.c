/*
 * Binary search tree specific operations implementation
 *
 */

#include "binary_search_tree.h"

int* bst_get(struct bt *t, key_t qKey) {
	bt_cursor n_pos = bst_search(*t->root, qKey);
	if(bt_isInternal(*n_pos))
		return &n_pos->data.value;
	return NULL;

}

void bst_put(key_t nKey, int nValue) {
	struct generic_data n_entry;
	n_entry.key = nKey;
	n_entry.value = nValue;
	bt_cursor n_pos = bst_search(*t->root, nKey);
	if(KEY_EQUAL(n_pos.data.key, nKey))
		n_pos->data.value = nValue;
	else
		bt_set_left(*n_pos, n_entry); 
}
/* Removes the entry associated with key qKey */
void bst_remove(key_t qKey) {
	bt_cursor n_pos = bst_search(*t->root, qKey);
	if(KEY_EQUAL(n_pos.data.key, qKey))
		bt_node_remove(n_pos);
}

/* Finds the parent of the node with key qKey 
 * This is the essence of binary search trees */
bt_cursor bst_search(struct bt_node n, key_t qKey) {
	if(KEY_EQUAL(n.data.key, qKey) || !bt_isInternal(n))
		return &n;
	if(KEY_GREATER(n.data.key, qKey))
		return bst_search(*n.left, qKey);
	return bst_search(*n.right, qKey);
}
/* Removes a node and replaces it with its left child */
void bst_node_remove(struct bt_node n) {
	

}

#endif
