/*
 *	Similar to B-tree, only that values are stored only at leaf nodes
 *	This allows a higher branching degree and a shallower tree
 */



class PlusIndex {
	string key;
public:
	Index(string key) : key(key) {}
	string getKey() {
		return this->key;
	}
		bool operator > (Index param) {
		return (key.compare(cmp.key)>0);
	}
	bool operator = (Index param) {
		return (key.compare(cmp.key)==0);
	}
	friend value(int value) {

}



class LeafIndex 
