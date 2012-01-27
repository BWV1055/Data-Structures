/*
 *	Weight balanced trees
 *		Original tree used irrational parameters, in Adams tree a bug was found
 *		See http://hagi.is.s.u-tokyo.ac.jp/~yh/bst.pdf
 *	This implementation uses delta = %delta% and gamma = %gamma%
 */

#include "BinarySearchTree.cpp"

class WBT_Node: public BSTNode {
	int size;
public: 
	WBT_Node(int size, WBT_Node* left, WBT_Node* right): size(size), left(left), right(right) {}
	int getSize() { return this->size; }
	int setSize(int size) { this->size = size; }
}

class WBT {
	WBT_Node* root;
public:
	WBT(): root(NULL) {}
	void insert(K key, V value) {
		this->base_add(key, value);
	}
}	

// Double rotation
void rotate_d_left(BSTNode* a) {
	BSTNode* b = a->right;
	BSTNode* c = b->left;
	c->parent = a->parent;
	if(a->parent) {
		if(a->parent->left==a)
			a->parent->left = c;
		else
			a->parent->right = c;
	}
	a->right = c->left;
	a->right->parent = a;
	b->left = c->right;
	b->left->parent = b;
	c->left = a;
	a->parent = c;
	c->right = b;
	b->parent = c;
}

void rotate_d_right(BSTNode* a) {
	BSTNode* b = a->left;
	BSTNode* c = b->right;
	c->parent = a->parent;
	if(a->parent) {
		if(a->parent->left==a)
			a->parent->left = c;
		else
			a->parent->right = c;
	}
	a->left = c->right;
	a->left->parent = a;
	b->right = c->left;
	b->right->parent = b;
	c->right = a;
	a->parent = c;
	c->left = b;
	b->parent = c;
}
