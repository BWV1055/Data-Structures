/*
 *	Skip node
 *	The node acts as a server for all nodes on its left
 *		and as a client for the nodes on its right
 *	It is assumed the list is sorted ascending, so usually
 *		nodes on the left send messages to nodes on the right
 *	All server sockets have to be open to accept queries
 *
 */

#ifndef _SKIP_NODE_H_
#define _SKIP_NODE_H_

#include "../../mds/mds_data_types.h"
#define SG_MAX_LEVELS	log(ULLONG_MAX+1)/log(2)

#define SG_SEARCH_OP	1
#define SG_INSERT_OP	2
#define SG_DELETE_OP	3


struct skip_node {
	int id;
	struct generic_data *data;
	uint32_t maxLevel;
	/* Server sockets are located on the left side of the node */
	int *soc_server_fd;
	/* arrays of predecessor IPs, ports, keys and ids */
	int *left_ips;
	int *left_ports;
	char **left_keys;
	int *left_ids;
	/* array of successor sockets */
	int *right_ips;
	int *right_ports;
	char **right_keys;
	int *right_ids;
	/* membership vector */
	unsigned long long m;
	char flags;
	/* Skip nodes on a machine form a list */
	struct skip_node *next;
};

typedef skip_node* sg_cursor;

/* Increase the height of sn by one */
void sn_increase_height(skip_node sn);
/* Set left/right neighbor sockets */
void sn_set_neighbors(skip_node sn, int left, int right, uint32_t level);
/* Select to which neighbor to send a new message */
char sn_select_neighbor(skip_node sn, key_t qKey);
/* Sends a message to a different machine 
 * The op is the operation code, the machine is referenced with the socket fd 
 * and qKey is the query key */
void sn_send_message(skip_node sn, char op, int out_socket, key_t qKey);
/* Add a new skip node with key qKey to the skip graph starting from skip node v */
void sn_add(skip_node v, key_t qKey);


#endif
