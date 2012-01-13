/*
 *	Linked list implementation in C++
 *
 *
 */

/* key-value type entries 
 * The key is currently not used, the sorting is done on value */
class Entry
{
	int value;
	std::string key;
public:
	Entry(int value, std::string key);
	int getValue();
	std::string getKey();
}

class AdjLLEntry
{
	Vertex* adjacent;
	AdjLLEntry *next;

public:
	void AdjLLEntry(Entry data, LLEntry *next);
	Entry getData();
	AdjLLEntry* getNext();
};

class AdjLinkedList
{
	int size;
	AdjLLEntry list[100];

public:
	void add(AdjLLEntry adj);
	AdjLLEntry remove();
	void walk((void*)(*f)(AdjLLEntry));
};
