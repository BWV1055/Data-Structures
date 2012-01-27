/*
 *	Splay tree
 */

class SplayTree: public BST {

public:
	void insert(K key, V value) {
		BSTNode* added = this->base_add(key, value);
		this->splay(added);
	}
	void remove(K key) {
		BSTNode<K,V>* pos = this->findPos(key, this->root);
		BSTNode<K,V>* parent = pos->parent;
		this->base_remove(key);
		if(parent)
			this->splay(parent);
	}
	void splay(BSTNode* x) {
		BSTNode* p = x->parent;
		if(!p)
			return;
		BSTNode* g = p->parent;
		if(!g) {
			if(p->left==x)
				rotate_right(p);
			else
				rotate_left(p);
			return;
		} 
		if(p->left==x&&g->left==p)
			zig_zig_right(x);
		else if(p->right==x&&g->right==p)
			zig_zig_left(x);
		else if(p->right==x&&g->left==p)
			rotate_d_right(x);
		else
			rotate_d_left(x);
		splay(x);
	}
}

void zig_zig_right(BSTNode* x) {
	BSTNode* p = x->parent;
	BSTNode* g = p->parent;
	if(g->parent) {
		if(g->parent->left==g)
			g->parent->left = x;
		else
			g->parent->right = x;
	}
	x->parent = g->parent;
	p->left = x->left;
	p->left->parent = p;
	g->left = p->right;
	g->left->parent = g;
	p->right = g;
	g->parent = p;
	x->right = p;
	p->parent = x;
}

void zig_zig_left(BSTNode* x) {
	BSTNode* p = x->parent;
	BSTNode* g = p->parent;
	if(g->parent) {
		if(g->parent->left==g)
			g->parent->left = x;
		else
			g->parent->right = x;
	}
	x->parent = g->parent;
	p->right = x->right;
	p->right->parent = p;
	g->right = p->left;
	g->right->parent = g;
	p->left = g;
	g->parent = p;
	x->left = p;
	p->parent = x;
}
