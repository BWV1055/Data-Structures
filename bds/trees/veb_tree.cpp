/*
 * van Emde Boas tree
 * van Emde Boas trees have update/search operations time or the order of
 * 	O(log log n), if keys are <=n. Space is O(n).
 * The wasted space is O(n), average n/2. Used if the number of elements is large.
 */

#include <cmath>
#include <vector>
using namespace std;

#define VEB_BITS	8
#define VEB_MAX	pow(2, VEB_BITS)

class VebAux;

class VebSubTree {
	int nBits;
	int max;
	int min;
	/* Values have maximum 2^nBits */
	vector<int> values;
	/* 2^(nBits/2) children each with nBits/2 bits */
	vector<VebSubTree*> children;
	/* has nBits/2 bits */
	VebAux* up;

public:
	/* nBits = 8 */
	VebSubTree(int nBits, bool aux) : nBits(nBits) {
		int i;
		int nBitsChd = nBits/2;
		int maxVal = 2^nBitsChd;

		this->values.reserve(maxVal);
		if(nBits==1 || aux)
			this->children = NULL;
		else
			for(i=0;i<maxVal;i++) {
				this->children[i] = VebSubTree(nBitsChd, 0);
			}
		this->min = maxVal;
		this->max = -1;

		if(!aux)
			this->up = new VebSubTree(nBitsChd, 1);
	}
	void put(int key, int value) {
		/* if(floor(log(2, key))!=this->nBits)
			return; */
		if(this->values.size()==0) {
			this->min = this->max = key;
			this->values.insert(this->values.begin()+key, value);
			return;
		}
		if(key<this->min) {
			tempKey = this->min;
			this->min = key;
			key = tempKey;
			tempValue = this->values[0];
			this->values[0] = value;
			value = tempValue;
		} 
		if(key>this->max) {
			tempKey = this->max;
			this->max = key;
			key = tempKey;
			tempValue = this->values[this->values.end()];
			this->values[this->values.end()] = value;
			value = tempValue;
		} 
		put_r(key, value);
	}
	void put_r(int key, int value) {
		int a = key>>(this->nBits/2);
		int b = key%(this->nBits/2);
		if(this->children[a]->values.size()==0)
			this->aux->put(key, value);
		this->children[a]->put(b, value);
	}
	int remove(int key) {
		if(this->values.size()==1) {
			this->min = 2^this->nBits;
			this->max = -1;
			int toReturn = this->values[key];
			this->values.erase(this->values.begin()+key);
			return toReturn;
		}
		if(this->min==key)
			this->min = key = this->aux->min*(2^(this->nBits/2))+this->children[this->aux->min]->min;
		return remove_r(key);
	}
	int remove_r(int key) {
		int a = key>>(this->nBits/2);
		int b = key%(this->nBits/2);
		this->children[a]->remove(b);
		if(this->children[a]->values.size()==0)
			this->aux->remove(a);
	}
	int findsucc(int key) {
		if(key<this->min)
			return this->min;
		if(key>this->max)
			return 2^this->nBits;
		/* Upper half bits are unchanged for the successor */
		int a = key>>(this->nBits/2);
		int b = key%(this->nBits/2);
		if(b<=this->children[a]->max)
			return (a<<(this->nBits/2)) + this->children[a]->findsucc(b);
		else
			return (a<<(this->nBits/2)) + this->children[this.aux->findsucc(a+1)].min;
	}
};
/* Keep statistics and locks if conccurent tree */
class VebTree {
	int min;
	int max;
	int size;
	VebSubTree* root;

public:
	VebTree() : min(-1), max(VEB_MAX), size(0) {
		this->root = new VebSubTree(VEB_BITS);
	}
	void put(int key, int value) {
		this->root->put(key, value);
	}
	int remove(int key) {
		return this->root->remove(key);
	}
	int findsucc(int key) {
		return this->root->findsucc(key);
	}
};
