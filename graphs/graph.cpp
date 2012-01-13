/*
 *	Graph class in C++
 *	Supports methods for adding/removing vertices, and traversing the graph
 *	This implementation uses an adjacency list to store the graph
 *
 *
 *
 */

class Entry
{
	int value;
	std::string key;
public:
	int getValue();
	std::string getKey();
}

class Vertex
{
	Entry entry;
	/* List of adjacent vertices */
	LinkedList adjList;

};

class Graph
{
	int size;
	Vertex vertices[100];

public:
	void addVertex(Vertex nVertex);
	Vertex removeVertex(Vertex qVertex);
	Vertex getVertex(Vertex qVertex);
	bool adjacent(Vertex fVertex, Vertex sVertex);
	Vertex[] neighbors(Vertex qVertex);
}

