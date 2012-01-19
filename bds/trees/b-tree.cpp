/*
 * B-tree implementation with classes
 */

#include <string>
#include <vector>

class Index {
	int value;
	string key;
public:
	Index(string key, int value) : key(key), value(value) {}
	string getKey() {
		return this->key;
	}
	int getValue() {
		return this->value;
	}
	bool operator > (Index param) {
		return (key.compare(cmp.key)>0);
	}
	bool operator = (Index param) {
		return (key.compare(cmp.key)==0);
	}
};

/* A node contains up to 2*K indices and 2*K+1 pointers */
class B-node {
	enum { K=5; }
	vector<Index> indices;
	vector<B-node*> children;
	B-node *parent;
public:
	B-node(Index first) : indices[0](first) {}
	B-node(Index first, B-node *child, B-node *parent) : indices[0](first), children[0](child), parent(parent) {}
	B-node(vector<Index> partIndices, int startInd, int endInd, vector<B-node*> partChildren, int startChd, int endChd) {
		int i=0;
		while(startInd<=endInd)
			this->indices[i++] = partIndices[startInd++];
		i=0;
		while(startChd<=endChd)
			this->children[i++] = partChildren[startChd++];
	}
	void addIndex(Index i) {
		int size = this->indices.size();
		int pos = findPos(i, 0, size);
		vector<Index>::iterator start = indices.begin();
		this->indices.insert(start+pos+1, i);
		size++;
		if(size==2*K+1) {
			B-node newNode = new B-node(this->indices, size/2+1, size, this->children, this->children.size()/2+1, this->children.size());
			startInd = indices.begin();
			vector<B-node*>::iterator startChd = children.begin();
			this->indices.erase(startInd, startInd+size/2+1);
			this->children.erase(startChd, startChd+this->children.size()/2+1);
			if(this->parent) {
				newNode->parent = this->parent;
				this->parent.addChild(&newNode);
				*this->parent.addIndex(this->indices[size/2]);
			} else {
				B-node newRoot = new B-node(this->indices[this->indices.size()/2]);
				newNode->parent = &newRoot;
				this->parent = &newRoot;
				newRoot.addChild(this);
				newRoot.addChild(newNode);
			}
		}
	}
	void addChild(B-node *child) {
		this->children.push_back(child);
	}
	void removeIndex(Index i) {
		int size = this->indices.size();
		int pos = findPos(i, 0, size);
		/* Leaf node */
		if(this->children.size()==0) {
			this->indices.remove(pos);
			if(this->indices.size()<K) {
				this->merge(this->parent->first());
			}
	}
	int getValueForKey(string key) {
		vector<Index>::iterator it;
		for(it=this->indices.begin();it<=this->indices.end();it++)
			if(key==this->indices[it].getKey())
				return this->indices[it].getValue();
	}
private:
	int findPos(Index i, int start, int end) {
		if(end-start<=0)
			return start;
		int half = (start+end)/2;
		if(indices[half]>i)
			return findPos(i, start, half);
		else if(i>indices[half])
			return findPos(i, half+1, end);
		else
			return half;
	}

};

class B-tree {
	B-node* root;
public:
	B-tree() {}
	/* Also updates existing key */
	void add(Index i) {
		B-node* pos = findPos(this->root, i);
		pos->addIndex(i);
	}
	void remove(Index i) {
		B-node* pos = findPos(this->root, i);
		pos->removeIndex(i);
	}
	int search(string key) {
		Index n = new Index(key, 0);
		B-node* pos = findPos(this->root, n);
		return pos->getValueForKey(key);
	}
private:
	/* Returns the node where Index i should be added 
	 * Search starts at start */
	B-node* findPos(B-node* start, Index i) {
		if(start==NULL)
			return start->parent;
		vector<Index>::iterator it;
		for(it=start->indices.start();it<=start->indices.end();it++)
			if(i<start->indices[it])
				break;
		return findPos(start->children[it+1], i);
	}
};

