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
	bool visited;
public:
	BSTNode(K key, V value): key(key), value(value), visited(false), left(NULL), right(NULL) {}

};

template <class K, class V>
class BST {
	BSTNode<K,V>* root;
	int total;
public:
	BST(): root(NULL), total(0) {}
	void add(K key, V value) {
		BSTNode<K,V>* pos = this->findPos(key, this->root);
		BSTNode* n = new BSTNode(key, value);
		if(pos->getKey()==key)
			return;
		n->parent = pos;
		if(pos->getKey()>key)
			pos->left = n;
		else
			pos->right = n;
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
};
