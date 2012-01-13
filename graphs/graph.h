/*
 *	The Graph class
 *
 *
 */

#include "adjacency_list.h"

class Graph
{
	int size;
	Vertex vertices[10];
	Edge edges[100];

public:
	Graph(int nSize, Vertex* nVertices) : size(nSize), vertices(nVertices) {}
	void addVertex(Vertex nVertex);
	Vertex removeVertex(Vertex qVertex);
	Vertex getVertex(Vertex qVertex);
	bool adjacent(Vertex fVertex, Vertex sVertex);
	Vertex[] neighbors(Vertex qVertex);


/* The format of the file:
 * 	First line contains the number of nodes
 * 	The next lines form a matrix with a value v greater than zero 
 *	at line s and column f if there is an edge of cost v between vertices
 *	s and f, or 0 if there is no edge between the nodes.
 * See graph_file.txt for an example of an unoriented graph.
 *
 * */
	void readFile(FILE *f);
	void writeFile(FILE *f);
};
