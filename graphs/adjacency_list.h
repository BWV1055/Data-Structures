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
typedef void* (&adjListWalk)(Edge, void*, void*);

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
	enum { UNDIRECTED = 0, DIRECTED = 1 };
	int cost;
	/* Directed/undirected edge */
	char flags;
	Vertex*	from;
	Vertex* to;
	/*
	Edge* start;
	Edge* end;
	*/
public:
	Edge(int nCost, Vertex* nTo, Vertex* nFrom, char nFlags=0) : cost(nCost), to(nTo), from(nFrom), flags(nFlags) {}
	bool isDirected();
	int getCost();
	void setCost(int nCost);
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
	/* Removes the first occurent of pair from the list */
	void removeEdge(Edge* pair);
	/* Check if there is an edge with qAdj */
	bool exists(const Vertex* qAdj);
	/* The second parameter of adjListWalk is used for bringing in additional data
	 *  to use with adjListWalk, and the third parameter is what adjListWalk returns 
	 * The walk stops when it receives a NULL, and it returns the third argument */
	const void* walk(adjListWalk f);
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
	Edge* addEdge(Vertex vertex, int cost);
	void removeEdge(Vertex vertex);
	int getCost(Vertex vertex);
	void setCost(Vertex vertex, int cost);
	bool checkAdjacency(Vertex vertex);
};




#endif
