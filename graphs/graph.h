/*
 *	The Graph class
 *
 *
 */

#include "adjacency_list.h"

class Graph
{
	vector<Vertex*> vertices;
	vector<Edge*> edges;

public:
	Graph() {}
	void addVertex(Vertex nVertex);
	Vertex removeVertex(Vertex qVertex);
	Vertex getVertex(Vertex qVertex);
	bool adjacent(Vertex fVertex, Vertex sVertex);
	vector<Vertex*> neighbors(Vertex qVertex);
	/* Vertices which are at the origin end, with qVertex at the destination end */ 
	vector<Vertex*> incoming(Vertex qVertex);
	int nEdges();

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
/* Check if graph is DAG (Directed Acyclic Graph) */
	bool isDAG();
/* Topological sorting of nodes */
	vector<int> topologicalSort();
	vector<int> topologicalSortDFS();
};
