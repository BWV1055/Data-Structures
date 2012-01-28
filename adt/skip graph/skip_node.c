/*
 * Skip node implementation
 */

#include "skip_node.h"
#include "socket_conn.h"

void sn_increase_height(skip_node sn);
	if(sn.maxLevel+1>SG_MAX_LEVELS)
		return;
	sn.maxLevel++;
	sn.left[maxLevel-1] = NULL;
	sn.right[maxLevel-1] = NULL;
}

void sn_set_neighbors(skip_node sn, int left, int right, uint32_t level) {
	if(level>=sn.maxLevel)
		return;
	sn.left[level] = left;
	sn.right[level] = right;
}
/* If qKey is greater, go to the next machine/next node in the list 
 * There is no need to store the data at the next node as long as the nodes are sorted */
char sn_select_neighbor(skip_node sn, key_t qKey, uint32_t level) {
	return (KEY_GREATER_OR_EQUAL(qKey, sn.data.key)?(KEY_EQUAL(qKey, sn.data.key)?0:1):-1);
}

uint32_t sg_search(sg_cursor start, key_t qKey) {
	int dir, level = start->maxLevel-1;
	dir = sn_select_neighbor(*start, qKey, level);
	if(dir==0)
		return start->address;
	else if(dir==1) {
		socket_send_message(start->soc_right_fd[level], 1, right[level], qKey);
		socket_read_message(start->soc_right_fd);
	}
	else {
		socket_send_message(start->soc_left_fd[level], 1, left[level], qKey);
		socket_read_message(start->soc_left_fd[level]);
	}
}
