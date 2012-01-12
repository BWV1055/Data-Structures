/*
 * Binary search tree specific operations implementation
 *
 */

#include "binary_search_tree.h"

int* bst_get(struct bt *t, key_t qKey) {
	bt_cursor res = bst_search(*t->root, qKey);
	if(bt_isInternal(*res))
		return &res->data.value;
	return NULL;

}

void bst_put(key_t nKey, int nValue) {


}
/* Removes the entry associated with key qKey */
void bst_remove(key_t qKey);

/* Finds the parent of the node with key qKey 
 * This is the essence of binary search trees */
bt_cursor bst_search(struct bt_node n, key_t qKey) {
	if(KEY_EQUAL(n.data.key, qKey) || !bt_isInternal(n))
		return &n;
	if(KEY_GREATER(n.data.key, qKey))
		return bst_search(*n.left, qKey);
	return bst_search(*n.right, qKey);
}

#endif
