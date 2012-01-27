/*
 *	Weight balanced trees
 *		Original tree used irrational parameters, in Adams tree a bug was found
 *		See http://hagi.is.s.u-tokyo.ac.jp/~yh/bst.pdf
 *	This implementation uses delta = %delta%, alpha = %alpha% and omega=%omega%
 */

#include "BinarySearchTree.cpp"

class WBT_Node: public BSTNode {
	enum {ALPHA=2, OMEGA=1, DELTA=4};
	int size;
public: 
	WBT_Node(): size(1), left(NULL), right(NULL) {} 
	WBT_Node(int size, WBT_Node* left, WBT_Node* right): size(left->size+right->size+1), left(left), right(right) {}
	int getSize() { return this->size; }
	int setSize(int size) { this->size = size; }
	void check_balance() {
		if(this->left->getSize()<this->right->getSize()*OMEGA+DELTA)
			select_rotation(L);
		else if(this->right->getSize()<this->left->getSize()*OMEGA+DELTA)
			select_rotation(R);
	}
	void select_rotation(bool LR) {
		WBT_Node* subtree;
		if(LR==L) {
			subtree = this->right;
			if(ALPHA*subtree->left->getSize()<subtree->right->getSize())
				rotate_left(this);
			else
				rotate_d_left(this);
		} else {
			subtree = this->left;
			if(ALPHA*subtree->right->getSize()<subtree->left->getSize())
				rotate_left(this);
			else
				rotate_d_left(this);
		}
	}

}

class WBT: public BST {
	WBT_Node* root;
public:
	WBT(): root(NULL) {}
	void insert(K key, V value) {
		WBT_Node* added = this->base_add(key, value);
		added->check_balance();
	}
	void delete(K key) {
		this->base_remove();
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
