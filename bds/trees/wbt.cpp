/*
 *	Weight balanced trees
 *		Original tree used irrational parameters, in Adams tree a bug was found
 *		See http://hagi.is.s.u-tokyo.ac.jp/~yh/bst.pdf
 *	This is the original version of the algorithm
 *	This implementation uses delta = 3, alpha = 1 and gamma=2
 */

#include "BinarySearchTree.cpp"

class WBT_Node: public BSTNode {
	enum {ALPHA=1, GAMMA=2, DELTA=3};
	int size;
public: 
	WBT_Node(): size(1), left(NULL), right(NULL) {} 
	WBT_Node(int size, WBT_Node* left, WBT_Node* right): size(left->size+right->size+1), left(left), right(right) {}
	/* Adams tree
	 * WBT_Node(int size, WBT_Node* left, WBT_Node* right): size(left->size+right->size), left(left), right(right) {}
	 */
	int getSize() { return this->size; }
	int setSize(int size) { this->size = size; }
	bool check_balance() {
		/* Adams tree 
		 * if(this->left->getSize()+this->right->getSize()<=1)
		 *	 return true;
		 */
		if(this->left->getSize()<this->right->getSize()*GAMMA+DELTA) {
			select_rotation(L);
			return false;
		}
		if(this->right->getSize()<this->left->getSize()*GAMMA+DELTA) {
			select_rotation(R);
			return false;
		}
		if(!this->right->check_balance())
			return false;
		if(!this->left->check_balance())
			return false;
		return true;
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
