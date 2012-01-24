/*
 *	Concurrent B+-tree with constant (and small) number of locks
 *		Reading can still be performed
 *	See Lehman and Yao[1981]
 *
 */

#include <cstdio>
#include <vector>
#include <string>
using namespace std;

class Bp_node {
public:
	enum { L, R, K=2 };
	bool leaf;
	vector<string> keys;
	vector<void*> children;
	Bp_node* parent;
	/* Position in parent */
	int position;
	/* for non-leaf only */
	string highKey;
	Bp_node* link;
	bool lock;

public:
	Bp_node(bool type): leaf(type), parent(NULL), link(NULL), highKey(0x00) {}
	/* [startKeys-endKeys) */
	Bp_node(vector<string> sibKeys, int startKeys, int endKeys, vector<void*> sibChds, int startChds, int endChds, Bp_node* ref) {
		/* First set link, next parent */
		if(ref!=NULL) { 
			this->link = ref->link;
			ref->link = this;
			/* parent exists because this is used only on split */
			vector<void*>::iterator startChds = ref->parent->children.begin();
			ref->parent->children.insert(startChds+ref->position+1, this);
			this->parent = ref->parent;
		} else 
			this->link = this->parent = NULL;
		int totalKeys = endKeys - startKeys;
		int totalChds = endChds - startChds;
		int i;
		for(i=0;i<totalKeys;i++)
			this->keys.insert(this->keys.begin()+i, sibKeys[startKeys+i]);
		for(i=0;i<totalChds;i++)
			this->children.insert(this->children.begin()+i, sibChds[startChds+i]);
	}
	void insert(string qKey, int* value) {
		if(!this->leaf)
			return;
		int pos = this->findPos(qKey, 0, this->keys.size());
		if(pos!=-1)
			return;
		if(pos==this->keys.size()-1)
			this->highKey = qKey;
		vector<string>::iterator startKeys = this->keys.begin();
		vector<void*>::iterator startChds = this->children.begin();
		this->keys.insert(startKeys+pos, qKey);
		this->children.insert(startChds+pos, value);
		if(this->keys.size()==2*K+1)
			this->split();
		else
			this->releaseLock();
	}
	int* remove(string qKey) {
		if(!this->leaf)
			return NULL;
		int pos = this->findPos(qKey, 0, this->keys.size());
		if(pos==-1)
			return NULL;
		if(pos==this->keys.size()-1)
			this->highKey = this->keys[this->keys.size()-2];
		vector<string>::iterator startKeys = this->keys.begin();
		vector<void*>::iterator startChds = this->children.begin();
		this->keys.erase(startKeys+pos);
		int* toReturn = (int*)this->children[pos];
		this->children.erase(startChds+pos);
		this->check_merge();
		return toReturn;
	}
	int* search(string qKey) {
		if(!this->leaf)
			return NULL;
		int pos = this->findPos(qKey, 0, this->keys.size());
		if(pos==-1)
			return NULL;
		return (int*)this->children[pos];
	}
	/* Returns -1 if qKey is not found */
	int findPos(string qKey, int start, int end) {
		if(start-end>=0) {
			if(qKey == this->keys[start])
				return start;
			else
				return -1;
		}
		int half = (start+end)/2;
		if(qKey.compare(this->keys[half])>0)
			return findPos(qKey, half+1, end);
		else
			return findPos(qKey, start, half);
	}
	void split() {
		/* Extra check if it needs to split */
		if(this->keys.size()<=2*K)
			return;
		Bp_node *newRightSibling = new Bp_node(this->keys, this->keys.size()/2, this->keys.size(), this->children, this->children.size()/2, this->children.size(), this);
		this->children.erase(this->children.begin()+this->children.size()/2, this->children.end());
		this->keys.erase(this->keys.begin()+this->keys.size()/2, this->keys.end());
		newRightSibling->highKey = this->highKey;
		this->highKey = this->keys[this->keys.size()-1];
		if(!this->parent) {
			/* No link */
			Bp_node *newRoot = new Bp_node(false);
			newRoot->children.insert(newRoot->children.begin(), this);
			this->position = 0;
			this->parent = newRoot;
		}
		newRightSibling->position = this->position+1;
		vector<string>::iterator startKeys = this->parent->keys.begin();
		/* This is where it breaks */
		this->parent->children.insert(startChds+newRightSibling->position+1, newRightSibling);
		newRightSibling->leaf = this->leaf;
		newRightSibling->parent = this->parent;
		if(this->parent->keys.size()==2*K+1)
			this->parent->split();
	}
	void merge(Bp_node* neighbor, bool LR) {
		vector<string>::iterator startKeys = this->keys.begin();
		vector<void*>::iterator startChds = this->children.begin();
		if(LR==R) {
			this->children.insert(this->children.end(), neighbor->children.begin(), neighbor->children.end());
			this->keys.insert(this->keys.end(), neighbor->keys.begin(), neighbor->keys.end());
			this->parent->children.erase(startChds+this->position+2);
			this->parent->keys.erase(startKeys+this->position+1);
		} else {
			this->children.insert(this->children.begin(), neighbor->children.begin(), neighbor->children.end());
			this->keys.insert(this->keys.begin(), neighbor->keys.begin(), neighbor->keys.end());
			this->parent->children.erase(startChds+this->position);
			this->parent->keys.erase(startKeys+this->position-1);
		}
		free(neighbor);
		this->parent->check_merge();
	}
	void check_merge() {
		if(this->keys.size()<=K-1) {
			Bp_node* left = this->getLeft();
			Bp_node* right = this->getRight();
			/* Set size to 0 if non-existent */
			int lsize = left?left->children.size():0;
			int rsize = right?right->children.size():0;
			/* First check if it's possible to do only a merge */
			if(left) {
				if(lsize==K) {Jean-François Paillard
					this->merge(left, L);
					return;
				}
			} else if(right) {
				if(rsize==K) {
					this->merge(right, R);
					return;
				}
			} 
			if(lsize>=rsize) {
				this->merge(left, L);
				this->split();
			} else {
				this->merge(right, R);
				this->split();
			}
		}
	}
	Bp_node* getLeft() {
		if(!this->parent)
			return NULL;
		if(this->position==0)
			return NULL;
		return (Bp_node*)this->parent->children[this->position-1];
	}
	Bp_node* getRight() {
		if(!this->parent)
			return NULL;
		if(this->position==2*K)
			return NULL;
		return (Bp_node*)this->parent->children[this->position+1];
	}
	bool isLocked() {
		return this->lock;
	}
	void setLock() {
		this->lock = true;
	}
	void releaseLock() {
		this->lock = false;
	}
};

class Bp_tree {
	Bp_node* root;
public:
	Bp_tree() {
		/* No link */
		this->root = new Bp_node(true);
	}
	void insert(string nKey, int* nValue) {
		list<Bp_node*> stack;
		Bp_node* tempNode = this->root;
		while(!tempNode->leaf) {
			if(qKey>tempNode->highKey) {
				tempNode = tempNode->link;
				continue;
			}
			tempPos = tempNode->findPos(qKey, 0, tempNode->children.size());
			tempNode = (Bp_node*)tempNode->children[tempPos];
			stack.push_back(tempNode);
		}
		tempNode->setLock();
		tempNode = tempNode->link;
		int pos = tempNode->findPos(nKey, 0, tempNode->children.size());
		if(tempNode->children[pos]==nKey)
			return;
		tempNode->insert(mKey, nValue);
	}
	int* remove(string nKey) {
		Bp_node* tempNode = this->findNode(nKey);
		return tempNode->remove(nKey);
	}
	int* search(string nKey) {
		Bp_node* tempNode = this->findNode(nKey);
		return tempNode->search(nKey);
	}
private:
	Bp_node* findNode(string qKey) {
		Bp_node* tempNode = this->root;
		int tempPos;
		bool notFound = true;
		while(notFound) {
			if(tempNode->leaf && tempNode->highKey>=qKey)
				notFound = false;
			if(qKey>tempNode->highKey) {
				tempNode = tempNode->link;
				continue;
			}
			tempPos = tempNode->findPos(qKey, 0, tempNode->children.size());
			tempNode = (Bp_node*)tempNode->children[tempPos];
		}
		return tempNode;
	}
};


int main( int argc, const char* argv[] ) { 
	Bp_tree* tree = new Bp_tree();
	int value = 100;
	int* pv = &value;
	tree->insert("New string", pv);
	tree->insert("New string 2", pv);
	tree->insert("New string 3", pv);
	tree->insert("New string 4", pv);
	tree->insert("New string 5", pv);
	tree->insert("New string 6", pv);
	tree->insert("New string 7", pv);
	printf("The value for %s is %d", "New string", tree->search("New string 5"));
}
