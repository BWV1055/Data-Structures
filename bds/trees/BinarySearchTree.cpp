/*
 *	Binary search tree in C++
 */

#include <vector>
using namespace std;

template <class K, class V>
class BSTNode {
	K key;
	V value;
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;
	int height;
	bool visited;
public:
	BSTNode(K key, V value): key(key), value(value), visited(false), left(NULL), right(NULL), height(0) {}
	int bFactor() { return this->left->getHeight() - this->right->getHeight(); }
	int getHeight() { return this->height; }
	int nChd() { return (this->left?1:0) + (this->right?1:0); }
};

template <class K, class V>
class BST {
	BSTNode<K,V>* root;
	int total;
public:
	BST(): root(NULL), total(0) {}
	BSTNode<K,V>* base_add(K key, V value) {
		BSTNode<K,V>* pos = this->findPos(key, this->root);
		BSTNode* n = new BSTNode(key, value);
		if(pos->getKey()==key)
			return NULL;
		n->parent = pos;
		if(pos->getKey()>key)
			pos->left = n;
		else
			pos->right = n;
		return n;
	}	

	void base_remove(K key) {
		BSTNode<K,V>* pos = this->findPos(key, this->root);
		if(pos->getKey()!=key)
			return;
		this->base_remove_r(pos);
	}

	V search(K key) {
		BSTNode<K,V>* pos = this->findPos(key, this->root);
		BSTNode* n = new BSTNode(key, value);
		if(pos->getKey()!=key)
		   return NULL;
		return pos->getValue();
	}	
private:
	/* If key exists, return the position, otherwise
	 * return the position of the presumed parent */
	BSTNode<K,V>* findPos(K key, BSTNode<K,V>* start) {
		if(start->getKey()==key) 
			return start;
		if(start->getKey()<key) {
		   	if(start->getLeft())
				return this->findPos(start->getLeft());
			else
				return start;
		}
		if(start->getRight())
			return this->findPos(start->getRight());
		return start;
	}

	void base_remove_r(BSTNode<K,V>* pos) {
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
		} else {
			child = pos->left;
			while(child->right)
				child = child->right;
			pos->value = child->value;
			this->base_remove_r(child);
		}
		free(pos);
	}
};
