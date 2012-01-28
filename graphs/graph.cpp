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

queue<Vertex*> Graph::DFS(Vertex* start) {
	queue<Vertex*> dfsVertices;
	this->DFS_r(start, dfsVertices);
	this->resetVisited();
	return dfsVertices;
}

void Graph::DFS_r(Vertex* start, queue<Vertex*> dfsVertices) {
	start->setVisited();
	dfsVertices.push(start);
	list<Vertex*> neighbors = this->neighbors(start); 
	while(!neighbors.empty()) {
		Vertex* next = neighbors.pop_back();
		if(!next->visited())
			this->DFS_r(next, dfsVertices);
	}
}

queue<Vertex*> Graph::BFS(Vertex* start) {
	queue<Vertex*> bfsVertices;
	start->setVisited();
	bfsVertices.push(start);
	this->BFS_r(start, bfsVertices);
	this->resetVisited();
	return bfsVertices;
}

void Graph::BFS_r(Vertex* start, queue<Vertex*> bfsVertices) {
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
		this->BFS_r(next, bfsVertices);
	}
}

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
	

