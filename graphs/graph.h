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
#include <algorithm>

template<class VertexT>
class DSN {
	VertexT* vertex;
	DSN* parent;
	int rank;
public:
	DSN(VertexT* vertex) : vertex(vertex), parent(this), rank(0) {}
	int getRank() { return this->rank; }
};

template<class VertexT>
class DSForest {
	vector<DSN<VertexT>*> roots;
public:
	DSForest() : roots(NULL) {}
	void makeDSN(VertexT* vertex) {
		DSN<VertexT>* newDSN = new DSN(vertex);
		this->roots.insert(this->roots.end(), newDSN);
	}
	void unionDSN(DSN<VertexT>* x, DSN<VertexT>* y) {
		this->link(this->findSet(x), this->findSet(y));
	}
	void link(DSN<VertexT>* x, DSN<VertexT>* y) {
		if(x->rank>y->rank) {
			y->parent = x;
			this->roots.erase(find(this->roots.begin(), this->roots.end(), y));
		} else {
			x->parent = y;
			this->roots.erase(find(this->roots.begin(), this->roots.end(), x));
			if(x->rank==y->rank)
				y->rank = y->rank+1;
		}
	}
	DSN<VertexT>* findSet(Vertex* qVertex) {
		if(qVertex->parent!=qVertex)
			qVertex->parent = this->findSet(qVertex->parent);
		return qVertex->parent;
	}
	bool sameSet(Vertex* fVertex, Vertex* sVertex) {
		return findSet(fVertex) == findSet(sVertex);
	}
};

class Graph
{
	enum { PLUS_INF_DISTANCE=1000 };
	vector<Vertex*> vertices;
	vector<Edge*> edges;

public:
	Graph() {}
	void addVertex(Vertex nVertex);
	Vertex removeVertex(Vertex* qVertex);
	/* pos is the position in the list of vertices */
	Vertex* getVertex(int pos);
	int findPos(Vertex* qVertex);
	bool adjacent(Vertex* fVertex, Vertex* sVertex);
	int getCost(Vertex* fVertex, Vertex* sVertex);
	list<Vertex*> neighbors(Vertex* qVertex);
	/* Vertices which are at the origin end, with qVertex at the destination end */ 
	list<Vertex*> incoming(Vertex* qVertex);
	int nEdges();
	int nVertices();
	queue<Vertex*> BFS(Vertex* start);
	queue<Vertex*> DFS(Vertex* start);
	bool isDAG();
/* Returns the positions in Graph::vertices reordered
 * Using topological sort ordering */
	vector<int> topologicalSort();
/* Another valid topological sort order of the vertices */
	vector<int> topologicalSortDFS();

/* G transposed has the same vertices and edges
 * If (u,v) is in G, (v,u) will be in G transposed */
	void transpose();
	DSForest* stronglyConnComponents();
/* Search algorithms */
	int* Dijkstra(Vertex* qVertex);
	int* DijkstraFib(Vertex* qVertex);


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
