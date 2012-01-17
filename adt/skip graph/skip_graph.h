/*
 * Skip graphs are a novel distributed data structure, based on skip lists, that provide the full
 * functionality of a balanced tree in a distributed system where resources are stored in separate
 * nodes that may fail at any time. They are designed for use in searching peer-to-peer systems, and
 * by providing the ability to perform queries based on key ordering, they improve on existing search
 * tools that provide only hash table functionality. Unlike skip lists or other tree data structures, skip
 * graphs are highly resilient, tolerating a large fraction of failed nodes without losing connectivity.
 * In addition, simple and straightforward algorithms can be used to construct a skip graph, insert
 * new nodes into it, search it, and detect and repair errors in a skip graph introduced due to node
 * failures.
 *	 
 *
 *
 */

#ifndef _SKIP_GRAPH_H_
#define _SKIP_GRAPH_H_

#include <math.h>
#include "skip_node.h"

struct skip_graph {
	struct skip_node *head;
	struct skip_node *nil;
	int size;
};

/* Returns the address where data with qKey is located, if it exists, 
 * or the address of the node storing the largest key less than qKey;
 * The search starts at a local node start */
uint32_t sg_search(sg_cursor start, key_t qKey);
/* Adds data to the skip graph
 * The new node starts to search for its position from the introductory node start, 
 * which is an existing node on the same machine */
void sg_add(sg_cursor start, struct generic_data data);


#endif
