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
	struct skip_node *start;
	struct skip_node *nil;
	int size;
};

struct skip_graph* sg_init() {
	struct skip_graph *n_sg = malloc(sizeof(*n_sg));
	struct skip_node *start = malloc(sizeof(*start));
	struct skip_node *nil = malloc(sizeof(*nil));

	key_t temp_key;
	struct generic_data temp_data;

	temp_key.name = 0x00;
	temp_key.len = 1;
	temp_data.value = 0;
	temp_data.key = temp_key;
	start->data = temp_data;

	temp_key.name = 0xff;
	temp_key.len = 1;
	temp_data.value = INT_MAX;
	temp_data.key = temp_key;
	nil->data = temp_data;

	nil->soc_server_fd = malloc(SG_MAX_LEVELS*sizeof(int));
	nil->soc_server_fd[0] = socket_open_server_socket(18440);
	nil->soc_left_fd = malloc(SG_MAX_LEVELS*sizeof(int));
	nil->soc_left_fd[0] = socket_open_comm_socket(start->soc_server_fd[0]);
	nil->maxLevel = 0;	

	start->soc_right_fd = malloc(SG_MAX_LEVELS*sizeof(int));
	start->soc_right_fd[0] = socket_connect("localhost", 18440);
	socket_send_message(start->soc_right_fd[0]
	start->maxLevel = 0;

	n_sg->start = start;
	n_sg->end = end;
	n_sg->size=0;

	return n_sg;
}

/* Returns the address where data with qKey is located, if it exists, 
 * or the address of the node storing the largest key less than qKey;
 * The search starts at a local node start */
uint32_t sg_search(sg_cursor start, key_t qKey);
/* Adds data to the skip graph
 * The new node starts to search for its position from the introductory node start, 
 * which is an existing node on the same machine */
void sg_add(sg_cursor start, struct generic_data data);


#endif
