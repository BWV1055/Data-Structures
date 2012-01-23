/*
 *	Red black tree methods definition
 *	The data structure for a red black tree is the 
 *		binary tree.
 *	The red black tree uses one bit in the flags field
 *		of the bt_node structure, and has specific update
 *		methods.
 *
 *
 *
 */

#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include "binary_search_tree.h"

#define RED	1
#define BLACK 0

#define BLACK_LEAF struct generic_data data; \
							key_t bl_key; \
							bl_key.name = 0x00; \
							bl_key.len = 0; \
							data.value = 0; \
							data.key = bl_key;

void rbt_put(struct bt* t, key_t nKey, int nValue);

void rbt_remove(struct bt* t, key_t qKey);


#endif
