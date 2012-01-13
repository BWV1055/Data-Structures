/*
 *	Linked list implementation in C++
 *
 *
 */

#include "adjacency_list.h"

const Edge* AdjacencyListEntry::getPair() {
	return this->pair;
}

const AdjacencyListEntry* AdjacencyListEntry::getNext() {
	return this->next;
}

void AdjacencyListEntry::setPair(Edge* nEdge) {
	this->pair = nEdge;
}

void AdjacencyListEntry::setNext(AdjacencyListEntry* nNext) {
	this->next = nNext;
}


void AdjacencyList::add(Edge pair) {
	AdjacencyListEntry newLE (&pair, NULL);
	this->size++;
	if(!this->size) {
		newLE.next = this->root;
		this->root = &newLE;
		this->tail = &newLE;
		return;
	}
	this->tail->next = &newLE;
	this->tail = &newLE;
}

Edge AdjacencyList::remove() {
	AdjacencyListEntry *behind, *it = this->root;
	while(it!=this->tail) {
		behind = it;
		it = it->next;
	}
	behind->next = NULL;
	this->tail = behind;
	delete it;
	this->size--;
}

void AdjacencyList::removeEdge(Edge* pair) {
	AdjacencyListEntry *behind, *it = this->root;
	if(this->root->pair==pair) {
		this->root = this->root->next;
		delete it;
		return;
	}
	while(it!=this->tail) {
		if(it->pair==pair) {
			behind->next = it->next;
			delete it;
			return;
		}
		behind = it;
		it = it->next;
	}
}

bool AdjacencyList::exists(const Vertex* qAdj) {
	AdjacencyListEntry* it = this->root;
	while(it) {
		if(it->pair->isPart(qAdj))
			return true;
		it = it->next;
	}
	return false;
}

/* If f returns NULL, walk() returns the position and stops there */
const void* AdjacencyList::walk(adjListWalk f) {
	AdjacencyListEntry* it = this->root;
	void* thirdParam;
	while(it) {
		if(!f(*it->pair, secondParam, thirdParam))
			return thirdParam;
		it = it->next;
	}
	return thirdParam;
}

bool Edge::isDirected() {
	return (bool)((this->flags & 2^DIRECTED)>>(DIRECTED-1));
}

int Edge::getCost() {
	return this->cost;
}

void Edge::setCost(int nCost) {
	this->cost = nCost;
}

EdgePair* Edge::getEndPoints() {
	EdgePair nPair;
	EdgePair* toReturn =& nPair;
	nPair[0] = this->from;
	nPair[1] = this->to;
	/* Returns address of local variable */
	return toReturn;
}

bool Edge::isPart(const Vertex* qVertex) {
	return ((this->from==qVertex) || (this->to==qVertex));
}

Entry Vertex::getData() {
	return this->data;
}

void Vertex::setData(Entry nData) {
	this->data = nData;
}

Edge* Vertex::addEdge(Vertex vertex, int cost) {
	Edge nPair (cost, this, &vertex);
	this->adjList.add(nPair);
}

void Vertex::removeEdge(Vertex vertex) {
	this->adjList.walk(remove_edge(vertex));
	AdjacencyListEntry* it = this->adjList.root;
	while(it) {
		if(it->pair->isPart(&vertex)) {
			this->adjList.removeEdge(it->pair);
			return;
		}
		it = it->next;
	}
}

int Vertex::getCost(Vertex vertex) {
	return this->adjList.walk(get_edge_cost(vertex));
	AdjacencyListEntry* it = this->adjList.root;
	while(it) {
		if(it->pair->isPart(&vertex))
			return it->pair->getCost();
		it = it->next;
	}
	return 0;
}

void Vertex::setCost(Vertex vertex, int cost) {
	this->adjList.walk(set_edge_cost(vertex, cost));
}

bool Vertex::checkAdjacency(Vertex vertex) {
	return this->adjList.walk(check_adj(vertex));
}

void* remove_edge(Edge pair, Vertex* vertex, void* empty) {
	if(pair.isPart(vertex))
}
		
