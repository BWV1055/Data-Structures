/*
 * Binary search tree specific operations definition
 *	Implements the Map ADT (unique keys)
 *
 *
 *
 *
 */

#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include "binary_tree.h"

/* Returns the value associated with key qKey, NULL if no such key exists */
int* bst_get(struct bt* t, key_t qKey);
/* Puts key nKey and value nValue as a new entry in the tree 
 * If the key exists, it replaces the value */
void bst_put(struct bt *t, key_t nKey, int nValue);
/* Removes the entry associated with key qKey */
void bst_remove(struct bt *t, key_t qKey);

#endif
