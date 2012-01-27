/*
 *	AVL tree in C++
 */

#include "BinarySearchTree.cpp"

template <class K, class V>
class AVL: public BST {
	void add(K key, V value) {
		BSTNode<K,V>* cur = this->base_add(key, value);
		if(!cur)
			return;
		while(cur) {
			/* Happens rarely, keep all in one if */
			if(abs(cur->bFactor())>1) {
				if(cur->bFactor()==-2) {
					if(cur->right->bFactor()==-1)
						rotate_left(cur);
					else {
						rotate_right(cur->right);
						rotate_left(cur);
					}
				} else {
					if(cur->left->bFactor()==1)
						rotate_right(cur);
					else {
						rotate_left(cur->left);
						rotate_right(cur);
					}
				}
			}
			cur = cur->parent;
		}
	}

	void remove(K key) {
		BSTNode<K,V>* pos = this->findPos(key, this->root);
		if(pos->getKey()!=key)
			return;
		this->remove(pos);
	}

	void remove(BSTNode<K,V>* pos) {
		BSTNode<K,V>* child;
		BSTNode<K,V>* temp;
		if(!pos->nChd()) { free(pos); return; }
		if(pos->nChd()==1) {
			child = pos->left?pos->left:pos->right;
			if(!pos->parent) {
				this->root = child;
			} else {
				child->parent = pos->parent;
				if(pos==pos->parent->left)
					pos->parent->left = child;
				else
					pos->parent->right = child;
			}
			free(pos);
		} else {
			child = pos->left;
			while(child->right)
				child = child->right;
			pos->value = child->value;
			temp = child;
			child = child->parent;
			this->remove_succ(temp);
			while(child) {
			/* Happens rarely, keep all in one if */
			if(abs(child->bFactor())>1) {
				if(child->bFactor()==-2) {
					if(child->right->bFactor()==-1)
						rotate_left(child);
					else {
						rotate_right(child->right);
						rotate_left(child);
					}
				} else {
					if(child->left->bFactor()==1)
						rotate_right(child);
					else {
						rotate_left(child->left);
						rotate_right(child);
					}
				}
			} else
				break;
			child = child->parent;
			}
		}
	}

	void remove_succ(BSTNode<K,V>* pos) {
		BSTNode<K,V>* child;
		if(!pos->nChd()) { free(pos); return; }
		if(pos->nChd()==1) {
			child = pos->left?pos->left:pos->right;
			if(!pos->parent) {
				this->root = child;
			} else {
				child->parent = pos->parent;
				if(pos==pos->parent->left)
					pos->parent->left = child;
				else
					pos->parent->right = child;
			}
		}
		free(pos);
	}
}
