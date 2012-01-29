/*
 *  Graph implementation
 *	Supports methods for adding/removing vertices, and traversing the graph
 *	This implementation uses an adjacency list to store the graph
 *
 *
 *  
 *
 *
 */

using namespace std;

#include "vertex.h"
#include "graph.h"




vector<int> Graph::topologicalSort() {
	vector<int> sortedPos;
	vector<int> startPos;
	int i, sPos;
	list<Vertex*> neighbors;
	for(i=0;i<this->vertices.size();i++)
		if(this->vertices[i]->inDegree()==0)
			startPos.push_back(i);
	while(!startPos.empty()) {
		/* Different valid order
		 * sPos = startPos[startPos.size()/2];
		 * startPos.erase(sPos); */
		sPos = startPos.pop_back();
		sortedPos.push_back(sPos);
		neighbors = this->neighbors(this->children[sPos]);
		while(!neighbors.empty()) {
			Vertex* neighbor = neighbors.pop_back();
			this->vertices[sPos]->removeEdge(neighbor);
			if(neighbor->inDegree()==0) {
				vector<Vertex*>::iterator neighborPos = std::find(this->children.begin(), this->children.end(), neighbor);
				sortedPos.push_back(neighborPos);
			}
		}
	}
	if(this->nEdges()) {
		cout << "The graph is not DAG" << endl;
		sortedPos.clear();
	}
	return sortedPos;
}

/* Visit nodes in DFS order */
vector<int> Graph::topologicalSortDFS() {
	vector<int> sortedPos;
	vector<int> startPos;
	int i, sPos;
	for(i=0;i<this->vertices.size();i++)
		if(this->vertices[i]->outDegree()==0)
			startPos.push_back(i);
	while(!startPos.empty()) {
		/* Different valid order
		 * sPos = startPos[startPos.size()/2];
		 * startPos.erase(sPos); */
		sPos = startPos.pop_back();
		visit_topSort(sPos);
	}	
	return sortedPos;
}

void visit_topSort(int sPos) {
	list<Vertex*> neighbors;
	Vertex* neighbor;
	if(!this->children[sPos]->visited()) {
		this->children[sPos]->setVisited();
		neighbors = this->incoming(*(this->children[sPos]));
		while(neighbors.size()) {
			neighbor = neighbors.pop_back();
			visit_topSort(neighbor);
		}
		sortedPos.push_back(sPos);
	}
}
/* Both dfsVertices and d/f/pre fields in each vertex can be used
 * O(V+E) 
 * Order=true, select neighbor with max f first; else, no predefined order */
queue<Vertex*> Graph::DFS(Vertex* start, bool order=false) {
	int time = 0;
	vector<Vertex*>::iterator it;
	for(it = this->vertices.begin(); it < this->vertices.end(); it++) {
		it->color = WHITE;
		it->pre = NULL;
	}
	queue<Vertex*> dfsVertices;
	this->DFS_visit(start, dfsVertices, time, order);
	return dfsVertices;
}

class compareByF {
	bool reverse;
public:
	compareByF(bool rev): reverse(rev) {}
	bool operator() (const Vertex* lhs, const Vertex* rhs) {
		if(reverse) return lhs->f>rhs->f;
		else return lhs->f<rhs->f;
	}
};

typedef priority_queue<Vertex*, <vector>Vertex*, compareByF> pq_fTime;

void Graph::DFS_visit(Vertex* start, queue<Vertex*> dfsVertices, int timestamp, bool order) {
	Edge* startNext;
	timestamp = timestamp+1;
	start->d = timestamp;
	start->color = GRAY;
	dfsVertices.push(start);
	list<Vertex*> neighbors = this->neighbors(start);
	/*
	list<Vertex*>::iterator it; 
	pq_fTime neighborso;
	for(it=neighbors.start();it<neighbors.end();it++)
		neighborso.add(it);
	*/
	while(!neighbors.empty()) {
		/* Changing the neighbor visit order results in another valid DFS 
		 * (for example, by selecting the minimum from the list each time) */
		Vertex* next = neighbors.pop();
		startNext = start->getEdge(next);
		if(next->color==WHITE) {
			next->pre = start;
			startNext->type = EDGE_TREE;
			this->DFS_visit(next, dfsVertices, timestamp);
		} else if(next->color==GRAY) {
			startNext->type = EDGE_BACK;
			/* Got here, it means the graph is not DAG */
		}
	}
	start->color = BLACK;
	timestamp = timestamp+1;
	start->f = time;
}

queue<Vertex*> Graph::BFS(Vertex* start) {
	queue<Vertex*> bfsVertices;
	start->setVisited();
	bfsVertices.push(start);
	this->BFS_visit(start, bfsVertices);
	this->resetVisited();
	return bfsVertices;
}

void Graph::BFS_visit(Vertex* start, queue<Vertex*> bfsVertices) {
	Vertex* next;
	list<Vertex*> neighbors = this->neighbors(start); 
	list<Vertex*>::iterator itNeighbors = neighbors.begin();
	for( ;itNeighbors!=neighbors.end;itNeighbors++) {
		next = *itNeighbors;
		if(!next->visited()) {
			next->setVisited();
			bfsVertices.push(next);
		}
	}
	itNeighbors = neighbors.start();
	for( ;itNeighbors!=neighbors.end;itNeighbors++) {
		next = *itNeighbors;
		this->BFS_visit(next, bfsVertices);
	}
}

/* nVertices values */
int* Graph::Dijkstra(Vertex* qVertex) {
	int i, nVertices = this->nVertices();
	int* distances = malloc(nVertices*sizeof(int));
	vector<Vertex*> unvisitedSet;
	Vertex* cur;
	list<Vertex*> neighbors;
	list<Vertex*>::iterator it;
	for(i=0;i<nVertices;i++) {
		distances[i] = PLUS_INF_DISTANCE;
		this->getVertex(i)->resetVisited();
		unvisitedSet.push_back(this->getVertex(i));
	}
	distances[this->findPos(qVertex)] = 0;
	this->getVertex(this->findPos(qVertex))->setVisited();
	unvisited.remove(this->findPos(qVertex));
	while(!unvisited.empty()) {
		cur = unvisitedSet.pop();
		neighbors = this->neighbors(cur);
		curPos = this->findPos(cur);
		for(it=neighbors->begin();it<neighbors->end();it++)
			if(!neighbors[it]->visited()) {
				cost = this->getCost(cur, neighbors[it]);
				if(distances[curPos]+cost<distances[this->findPos(neighbors[it])])
					distances[this->findPos(neighbors[it])] = distances[curPos]+cost;
			}
		this->getVertex(curPos)->setVisited();
	}
	/* free after using */
	return distances;
}

int* Graph::DijkstraFib(Vertex* qVertex) {
	int i, nVertices = this->nVertices();
	int* distances = malloc(nVertices*sizeof(int));
	FibHeap<Vertex*> unvisitedSet = new FibHeap();
	Vertex* cur;
	list<Vertex*> neighbors;
	list<Vertex*>::iterator it;
	for(i=0;i<nVertices;i++) {
		distances[i] = PLUS_INF_DISTANCE;
		this->getVertex(i)->resetVisited();
		unvisitedSet.insert(distances[i], this->getVertex(i));
	}
	unvisitedSet.decreaseKey(PLUS_INF_DISTANCE, qVertex);
	this->getVertex(this->findPos(qVertex))->setVisited();
	unvisitedSet.removeMin();
	while(!unvisitedSet.empty()) {
		cur = unvisitedSet->findMin();
		neighbors = this->neighbors(cur);
		curPos = this->findPos(cur);
		for(it=neighbors->begin();it<neighbors->end();it++)
			if(!neighbors[it]->visited()) {
				/* Always happens */
				cost = this->getCost(cur, neighbors[it]);
				if(distances[curPos]+cost<distances[this->findPos(neighbors[it])])
					/* Always happens */
					/* distances[this->findPos(neighbors[it])] = distances[curPos]+cost; */
					unvisitedSet->decreaseKey(distances[this->findPos(neighbors[it])] - distances[curPos]-cost, neighbors[it]);
			}
		this->getVertex(curPos)->setVisited();
	}
	return distances;
}
		
DSForest* stronglyConnComponents() {
	DSForest<Vertex>* newForest = new DSForest();
	vector<Vertex*>::iterator it;
	for(it = this->vertices.begin(); it < this->vertices.end(); it++)
		newForest->makeDSN(it);
	
	this->DFS();
	this->transpose();
	bool maxHeap = true;
	this->DFS(maxHeap);
	
	for(it = this->vertices.begin(); it < this->vertices.end(); it++) {
		if()
			newForest->unionDSN(newForest->findSet(it), %%);
	}
	return newForest;
}
	
