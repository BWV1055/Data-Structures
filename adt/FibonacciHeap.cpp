/*
 *	Fibonacci heap
 *
 */

// for NULL
#include <cstring>

/* Integer key, string value */
template<class V>
class Node {
	int key;
	V value;
	int rank;
	bool marked;
	Node<V>* parent;
	Node<V>* childrenList;
	Node<V>* next;
	Node<V>* prev;
public:
	Node(int nKey, V nValue): key(nKey), value(nValue), parent(NULL) {
		this->next = this;
		this->prev = this;
		this->childrenList = NULL;
		this->marked = false;
	}
	void link(Node* friendNode) {
		friendNode->prev = this->childrenList->prev;
		friendNode->next = this->childrenList;
		friendNode->parent = this;
		this->childrenList->prev->next = friendNode;
		this->childrenList->prev = friendNode;
		this->rank++;
		/* --- Marking section --- */
		friendNode->marked = false;
	}
};

template<class V>
class FibHeap {
	/* One of the roots 
	 * This root has the minimum key */
	Node<V>* minimumNode;
	/* Maximum 100 trees in the heap */
	Node<V>* rankArray[100];
public:
	FibHeap(): minimumNode(NULL)  {}
	/* Returns newly created node 
	 * O(1) amortized time */
	Node<V>* insert(int nKey, V nValue) {
		FibHeap<V>* newHeap = new FibHeap;
		newHeap->minimumNode = new Node(nKey, nValue);
		this->minimumNode = this->merge(newHeap);
	}
	/* O(1) amortized time */
	Node<V>* findMin() {
		return this->minimumNode;
	}
	/* O(log n) amortized time */
	void removeMin() {
		Node<V>* chd = this->minimumNode->childrenList;
		Node<V>* chdNext, *it;
		int rank = this->minimumNode->rank;
		/* Remove minimumNode from list */
		this->minimumNode->next->prev = this->minimumNode->prev;
		this->minimumNode->prev->next = this->minimumNode->next;
		chdNext = this->minimumNode;
		this->minimumNode = this->minimumNode->next;
		free(chdNext);
		it=this->minimumNode;
		do {
			rankArray[it->rank] = it;
			it = it->next;
		} while(it!=this->minimumNode);
		while(rank) {
			chdNext = chd->next;
			while(rankArray[chd->rank]!=NULL) {
				rankArray[chd->rank]->next->prev = rankArray[chd->rank]->prev;
				rankArray[chd->rank]->prev->next = rankArray[chd->rank]->next;
				/* chd rank is increased by one */
				chd->link(rank[chd->rank]);
			}
			chd->next = this->minimumNode;
			chd->prev = this->minimumNode->prev;
			this->minimumNode->prev->next = chd;
			this->minimumNode->prev = chd;
			chd = chdNext;
			rank--;
		}
		memcpy(&this->rankArray, NULL, 100);
	}
	/* O(1) amortized time */
	void merge(Node* friendHeapminimumNode) {
		if(this->minimumNode->key<friendHeapminimumNode->key) {
			friendHeapminimumNode->prev->next = this->minimumNode;
			friendHeapminimumNode->prev = this->minimumNode->prev;
			tempNode = this->minimumNode->prev;
			this->minimumNode->prev = friendHeapminimumNode->prev;
			tempNode->next = friendHeapminimumNode;
		} else {
			this->minimumNode->prev->next = friendHeapminimumNode;
			this->minimumNode->prev = friendHeapminimumNode->prev;
			tempNode = friendHeapminimumNode->prev;
			friendHeapminimumNode->prev = this->minimumNode->prev;
			tempNode->next = this->minimumNode;
			this->minimumNode = friendHeapminimumNode;
		}
	}
			
	/* O(1) amortized time 
	 * decreasing the key of i preserves heap order within the subtree rooted at x, though it may violate heap order between x and its parent
	 * this is why this subtree is added to the root list */
	void decreaseKey(int delta, Node<V>* qNode) {
		qNode->key -= delta;
		if(!qNode->parent)
			return;
		qNode->prev->next = qNode->next;
		qNode->next->prev = qNode->prev;
		qNode->prev = qNode->next = NULL;
		qNode->parent->rank--;
		/* --- Marking section --- */
		if(qNode->parent->parent) {
			if(!qNode->parent->marked)
				qNode->parent->marked = true;
			else
				/* Cascading cuts */
				decreaseKey(0, qNode->parent);
		}
		qNode->parent = NULL;
		this->minimumNode->link(qNode);
		if(this->minimumNode->key>this->minimumNode->prev->key)
			/* minimumNode->prev is qNode */
			this->minimumNode = this->minimumNode->prev;
	}
	/* O(log n) amortized time */
	void remove(Node<V>* qNode) {
		Node<V>* temp = this->minimumNode;
		/* Cut the link with the parent and add it to the list of roots */
		this->decreaseKey(0, qNode);
		this->minimumNode = qNode;
		/* Delete it and add its children to the list of roots */
		this->removeMin();
		this->minimumNode = temp;
	}
};
