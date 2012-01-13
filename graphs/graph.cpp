/*
 *	Graph class in C++
 *	Supports methods for adding/removing vertices, and traversing the graph
 *	This implementation uses an adjacency list to store the graph
 *
 *
 *
 */

class Vertex
{
	Entry entry;
	/* List of adjacent vertices */
	AdjLinkedList adjList;

};

class Edge
{
	int value;
	char flags;
	Vertex*	from;
	Vertex* to;

public:
	Edge(int value, Vertex* to, Vertex* from, char flags=0);
	int getValue();
	Vertex[] getEndPoints();
	bool isDirected();
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

