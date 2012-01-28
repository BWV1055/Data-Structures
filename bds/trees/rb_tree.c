/*
 *	Red-black tree update operations
 *	Requires maximum three rotations
 *	Credit to wikipedia
 */

#include "rb_tree.h"

void rbt_put(struct bt* t, key_t nKey, int nValue) {
	bt_cursor temp = bst_search(nKey);
	struct generic_data data;
	data.key = nKey;
	data.value = nValue;
	if(!strcmp(temp->data.key, nKey.name)) {
		mds_error(1, "Key already exists");
		return;
	}
	if(strcmp(temp->data.key, nKey.name)>0) {
		bt_set_left(*temp, data); 
		temp->left->flags = RED;
		bt_set_left(*temp->left, BLACK_LEAF);
		bt_set_right(*temp->left, BLACK_LEAF);
		insert_case1(temp->left);
	} else {
		bt_set_right(*temp, data);
		temp->right->flags = RED;
		bt_set_left(*temp->right, BLACK_LEAF);
		bt_set_right(*temp->right, BLACK_LEAF);
		insert_case1(temp->right);
	}
}

void rbt_remove(struct bt* t, key_t qKey) {
	bt_cursor temp = bst_search(nKey);
	struct generic_data data;
	data.key = nKey;
	data.value = nValue;
	if(strcmp(temp->data.key, nKey.name)) {
		mds_error(1, "Key does not exist");
		return;
	}
	
}

bt_cursor grandparent(bt_cursor cur) {
	if(cur!=NULL && cur->parent!=NULL)
		return cur->parent->parent;
	return NULL;
}

bt_cursor uncle(bt_cursor cur) {
	bt_cursor gp = grandparent(cur);
	if(!gp)
		return NULL;
	return (cur->parent==gp->left)?g->right:g->left;
}

bt_cursor sibling(bt_cursor cur) {
    if (cur == cur->parent->left)
        return cur->parent->right;
    else
        return n->parent->left;
}

void insert_case1(bt_cursor cur) {
	if (!cur->parent)
		cur->flags = BLACK;
    else
        insert_case2(cur);
}

void insert_case2(bt_cursor cur) {
    if (cur->parent->flags == BLACK)
         return;
    else
        insert_case3(cur);
}

void insert_case3(bt_cursor cur) {
    bt_cursor u = uncle(cur), gp;
 
    if ((u != NULL) && (u->flags == RED)) {
         n->parent->flags = BLACK;
         u->flags = BLACK;
         gp = grandparent(cur);
         gp->flags = RED;
         insert_case1(gp);
    } else
         insert_case4(cur);
}

void insert_case4(bt_cursor cur) {
    bt_cursor gp = grandparent(cur);
 
    if ((cur == cur->parent->right) && (cur->parent == gp->left)) {
         rotate_left(cur->parent);
         cur = cur->left;
    } else if ((cur == cur->parent->left) && (cur->parent == gp->right)) {
         rotate_right(cur->parent);
         cur = cur->right;
    }
    insert_case5(cur);
}

void insert_case5(bt_cursor cur) {
        bt_cursor gp = grandparent(cur);
 
        cur->parent->flags = BLACK;
        gp->flags = RED;
        if ((cur == cur->parent->left) && (cur->parent == gp->left)) {
                rotate_right(gp);
        } else if ((cur == cur->parent->right) && (cur->parent == gp->right)) {
                rotate_left(gp);
        }
}

void bt_replace_node(bt_cursor cur, bt_cursor child) {
	child->parent = cur->parent;
	if(cur->parent->left==cur)
		cur->parent->left = child;
	else
		cur->parent->right = child;
	free(cur);
}

void delete_one_child(bt_cursor cur) {
    bt_cursor child = bt_isInternal(cur->right)?cur->left:cur->right;
    bt_replace_node(cur, child);
    if (cur->flags == BLACK) {
        if (child->flags == RED)
            child->flags = BLACK;
        else
             delete_case1(child);
    }
    free(cur);
}

void delete_case1(bt_cursor cur) {
        if (cur->parent != NULL)
                delete_case2(cur);
}

void delete_case2(bt_cursor cur) {
    bt_cursor sb = sibling(cur);
 
    if (sb->flags == RED) {
        cur->parent->flags = RED;
        sb->flags = BLACK;
        if (cur == cur->parent->left)
            rotate_left(cur->parent);
        else
            rotate_right(cur->parent);
    } 
    delete_case3(cur);
}

void delete_case3(bt_cursor cur) {
    bt_cursor sb = sibling(cur);
 
    if ((cur->parent->flags == BLACK) &&
        (sb->flags == BLACK) &&
        (sb->left->flags == BLACK) &&
        (sb->right->flags == BLACK)) {
        sb->flags = RED;
        delete_case1(cur->parent);
    } else
    	delete_case4(cur);
}

void delete_case4(bt_cursor cur) {
    bt_cursor sb = sibling(cur);
 
    if ((cur->parent->flags == RED) &&
        (sb->flags == BLACK) &&
        (sb->left->flags == BLACK) &&
        (sb->right->flags == BLACK)) {
         sb->flags = RED;
         cur->parent->flags = BLACK;
     } else
         delete_case5(cur);
}

void delete_case5(bt_cursor cur) {
    bt_cursor sb = sibling(cur);
 
    if(sb->flags == BLACK) { 
        if ((cur == cur->parent->left) &&
            (sb->right->flags == BLACK) &&
            (sb->left->flags == RED)) { 
            sb->flags = RED;
            sb->left->flags = BLACK;
            rotate_right(sb);
        } else if ((cur == cur->parent->right) &&
            (sb->left->flags == BLACK) &&
            (sb->right->flags == RED)) {
            sb->flags = RED;
            sb->right->flags = BLACK;
            rotate_left(sb);
        }
    }
    delete_case6(cur);
}

void delete_case6(bt_cursor cur) {
    bt_cursor sb = sibling(cur);
 
    sb->flags = cur->parent->flags;
    cur->parent->flags = BLACK;
 
    if (cur == cur->parent->left) {
        sb->right->flags = BLACK;
        rotate_left(cur->parent);
    } else {
        sb->left->flags = BLACK;
        rotate_right(cur->parent);
    }
}

