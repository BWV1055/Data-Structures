/*
 * Adjancency matrix and vertex class
 *
 *
 */

#ifndef _ADJACENCY_MATRIX_H_
#define _ADJACENCY_MATRIX_H_

#include <iostream>
#include <string>

using namespace std;

class AdjacencyMatrix
{
	int size;
	Edge* references[size][size];
	AdjacencyMatrix(int size): size(size) {}
	void addRef(int i, int j, Edge* ref);
}

class Data
{
	std::string strVal;
	int intVal;
};
/* Same methods as class Vertex from adjacency_list.h */
class Vertex
{
	Data data;
	int index;
	char flags;
};

class Edge
{


};

#endif
