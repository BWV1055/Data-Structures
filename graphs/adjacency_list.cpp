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
int AdjacencyList::walk(adjListWalk f) {
	AdjacencyListEntry* it = this->root;
	int pos = 0;
	while(it) {
		if(!f(*it->pair))
			return pos;
		it = it->next;
		pos++;
	}
	return pos;
}
