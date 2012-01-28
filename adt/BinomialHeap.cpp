/*
 * A binomial heap is a collection of trees
 * It allows merging of two trees in O(log n), insert/delete are the same
 * 	as for the binary heap (O(log n)).
 */

#include <vector>
using namespace std;

/* 2^order data pieces */
template<class T>
class BinomialTree {
	T data;
	int order;
	vector<BinomialTree<T>*> children;
public:
	BinomialTree<T>* merge(BinomialTree<T>* friendTree) {
		BinomialTree<T>* newTree = new BinomialTree();
		if(friendTree->getOrder()!=this->getOrder)
			return NULL;
		if(friendTree->getRootKey()<this->getRootKey())
			newTree = this->addSubTree(friend);
		else
			newTree = friend->addSubTree(this);
		return newTree;
	}
	void addSubTree(BinomialTree<T>* friendTree) {
		this->setOrder(this->getOrder()+1);
		this->children.insert(this->children.begin(), friendTree);
	}
}

class BinomialHeap {
	int n;
	vector<BinomialTree<T>*> trees;
	BinomialTree<T>* minPos;
public:
	BinomialHeap* merge(BinomialHeap* friendHeap) {
		BinomialHeap* newHeap = new BinomialHeap();
		BinomialTree* itTree;
		vector<BinomialTree<T>*>::iterator it;
		for(it=this->trees.begin();it<max(this->tree.end(), friendHeap->tree.end());it++) {
			itTree = this->trees[it]->merge(friendHeap->trees[it]);
			if(newHeap->trees[it+1])
				newHeap->trees[it+1] = newHeap->trees[it+1]->merge(itTree);
			else
				newHeap->trees.insert(it+1, itTree);
		}
		return newHeap;
	}
	void insert(T data) {
		BinomialHeap* newHeap = new BinomialHeap(data);
		this = this->merge(newHeap);
	}
	data min() {
		return this->minPos->data;
	}
	void deleteMin() {
		BinomialHeap* newHeap = new BinomialTree();
		BinomialTree<T>* tTree;
		while(!this->minPos->children.empty()) {
			tTree = this->minPos->children.pop();
			newTree->merge(tTree);
		}
		this->merge(newHeap);
	}
}
