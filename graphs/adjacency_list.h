/*
 *
 *
 */

#ifndef _ADJACENCY_LIST_H_
#define _ADJACENCY_LIST_H_

#include <iostream>
#include <string>

using namespace std;

class Entry;
class Edge;
class AdjacencyListEntry;
class AdjacencyList;
class Vertex;

typedef Vertex* EdgePair[2];
typedef void* (&adjListWalk)(Edge);

/* key-value type entries 
 * The key is currently not used, the sorting is done on value */
class Entry
{
	int value;
	std::string key;
public:
	Entry(int nValue, std::string nKey) : value(nValue), key(nKey) {}
	Entry(int nValue) : value(nValue) {}
	int getValue();
	void setValue(int nValue);
	std::string getKey();
};

class Edge
{
	static const int UNDIRECTED = 0;
	static const int DIRECTED = 1;	
	int cost;
	/* Directed/undirected edge */
	char flags;
	Vertex* to;
	Vertex*	from;
	/*
	Edge* start;
	Edge* end;
	*/
public:
	Edge(int nCost, Vertex* nTo, Vertex* nFrom, char nFlags=0) : cost(nCost), to(nTo), from(nFrom), flags(nFlags) {}
	bool isDirected();
	int getCost();
	void setCost();
	EdgePair* getEndPoints();
	/* Returns true if qVertex is either end of the edge */
	bool isPart(const Vertex* qVertex);
};

class AdjacencyListEntry
{
public:
	Edge* pair;
	AdjacencyListEntry* next;

public:
	AdjacencyListEntry(Edge* nPair, AdjacencyListEntry* nNext) : pair(nPair), next(nNext) {}
	const Edge* getPair();
	const AdjacencyListEntry* getNext();
	void setPair(Edge* nPair);
	void setNext(AdjacencyListEntry* nNext);
};
/* Holds the pairs in which a vertex belongs */
class AdjacencyList
{
public:
	int size;
	AdjacencyListEntry* root;
	AdjacencyListEntry* tail;
public:
	AdjacencyList() : size(0), root(NULL), tail(NULL) {}
	/* void setRoot(AdjacencyListEntry* nRoot); */
	/* Adds a new vertex on the last position of the list */
	void add(Edge pair);
	/* Removes and returns the last pair in the list */
	Edge remove();
	/* Check if there is an edge with qAdj */
	bool exists(const Vertex* qAdj);
	int walk(adjListWalk f);
};

class Vertex
{
	Entry data;
	/* List of adjacent vertices */
	AdjacencyList adjList;
public:
	Vertex(Entry nData, AdjacencyList nAdjList = NULL) : data(nData), adjList(nAdjList) {}
	Entry getData();
	void setData(Entry nData);
	Edge* addEdge(Vertex nVertex);
	void removeEdge(Vertex nVertex);
	int getCost(Vertex nVertex);
	void setCost(Vertex nVertex);
	bool checkAdjacency(Vertex nVertex);
};




#endif
