/*
 *	Graph implemented using an adjacency list
 *
 *
 */

#include "adjacency_list.h"
/*
 * #include "adjacency_matrix.h"
 */
#include <queue>

class Graph
{
	vector<Vertex*> vertices;
	vector<Edge*> edges;

public:
	Graph() {}
	void addVertex(Vertex nVertex);
	Vertex removeVertex(Vertex* qVertex);
	/* pos is the position in the list of vertices */
	Vertex* getVertex(int pos);
	bool adjacent(Vertex fVertex, Vertex sVertex);
	list<Vertex*> neighbors(Vertex* qVertex);
	/* Vertices which are at the origin end, with qVertex at the destination end */ 
	list<Vertex*> incoming(Vertex* qVertex);
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

	queue<Vertex*> DFS(Vertex* start);
	queue<Vertex*> BFS(Vertex* start);
/* Returns the positions in Graph::vertices reordered
 * Using topological sort ordering */
	vector<int> topologicalSort();
/* Another valid topological sort order of the vertices */
	vector<int> topologicalSortDFS();
/* Check if graph is Directed Acyclic Graph */
	bool isDAG();

	void resetVisited();
};
