/*
 * Binary search tree specific operations implementation
 * 	The remove operation is specific to binary search trees
 *
 */

#include "binary_search_tree.h"

int* bst_get(struct bt *t, key_t qKey) {
	bt_cursor n_pos = bst_search(t->root, qKey);
	if(bt_isInternal(*n_pos))
		return &n_pos->data.value;
	return NULL;
}

void bst_put(key_t nKey, int nValue) {
	struct generic_data *n_entry = malloc(sizeof(*n_entry));
	n_entry->key = nKey;
	n_entry->value = nValue;
	bt_cursor n_pos = bst_search(t->root, nKey);
	if(KEY_EQUAL(n_pos.data.key, nKey))
		n_pos->data.value = nValue;
	else if(KEY_GREATER(n_pos.data.key, nKey))
		bt_set_left(*n_pos, *n_entry); 
	else
		bt_set_right(*n_pos, *n_entry);
}

void bst_remove(key_t qKey) {
	bt_cursor n_pos = bst_search(t->root, qKey);
	if(KEY_EQUAL(n_pos.data.key, qKey))
		bst_node_remove(n_pos);
}

/* Finds the node with key qKey 
 * This is the essence of binary search trees */
bt_cursor bst_search(bt_cursor cur, key_t qKey) {
	if(KEY_EQUAL(cur->data.key, qKey) || !bt_isInternal(*cur))
		return cur;
	if(KEY_GREATER(cur->data.key, qKey))
		return bst_search(cur->left, qKey);
	return bst_search(cur->right, qKey);
}
/* Removes a node and replaces it with its left child 
 * The right child will become the right-most node of the left child */
void bst_node_remove(bt_cursor cur) {
	bt_cursor temp = cur;
	if(!bt_isInternal(cur)) {
		cur = cur->parent;
		cur = (cur->left==temp?cur->left=NULL:cur->right=NULL);
		free(temp);
	}
	if(bt_get_left(*cur) && bt_get_right(*cur)) {
		cur = cur->left;
		while(cur->right)
			cur = cur->right;
		temp->data = cur->data;
		bst_node_remove(cur);
		return;
	}
	if(bt_get_left(*cur)) {
		cur->left->parent = cur->parent;
		cur->parent->left = cur->left;
		free(cur);
	}
}
