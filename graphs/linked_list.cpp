/*
 *	Linked list implementation in C++
 *
 *
 */

using namespace std;

/* key-value type entries 
 * The key is currently not used, the sorting is done on value */
class Entry
{
	int value;
	std::string key;
public:
	Entry(int nValue, std::string nKey) : value(nValue), key(nKey) {}
	int getValue();
	std::string getKey();
}



class AdjLLEntry
{
public:
	Vertex* adjacent;
	AdjLLEntry* next;

public:
	AdjLLEntry(Vertex* nAdjacent, AdjLLEntry* nNext) : adjacent(nAdjacent), next(nNext) {}
	setAdjacent(Vertex* adj);
	setNext
	Vertex* getAdjacent();
	AdjLLEntry* getNext();
};

Vertex* AdjLLEntry::getAdjacent() {
	return this->adjacent;
}

AdjLLEntry* getNext() {
	return this->next;
}

class AdjLinkedList
{
public:
	int size;
	AdjLLEntry* root;
	AdjLLEntry* tail;
public:
	AdjLinkedList(int nSize = 0) : size(nSize), root(NULL) {}
	void setRoot(AdjLLEntry* nRoot);
	void add(Vertex* adj);
	AdjLLEntry remove();
	void walk((void*)(*f)(AdjLLEntry));
};

void AdjLinkedList::add(Vertex* adj) {
	AdjLLEntry newAdj (adj, NULL);
	if(!this->size) {
		newAdj->setNext(this->root);
		this->setRoot(&newAdj);
		return;
	}
	this->tail->next = &newAdj;
	this->tail = &newAdj;
}

AdjLLEntry AdjLinkedList::remove() {
	AdjLLEntry* behind, it = this->root;
	while(it!=tail) {
		behind = it;
		it = it->next;
	}
	behind->next = NULL;
	this->tail = behind;
	delete it;
}
/* If f returns NULL, walk() returns the position and stops there */
int AdjLinkedList::walk((void*)(*f)(AdjLLEntry)) {
	AdjLLEntry* it = this->root;
	int pos = 0;
	while(it) {
		if(!f(*it))
			return pos;
		it = it->next;
		pos++;
	}
	return pos;
}
