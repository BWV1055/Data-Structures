/*
 *	This is the server which holds the start and nil nodes (and possibly its own data),
 *	and various skip graph statistics.
 *	Read README.txt for message type format.
 *	
 *
 */

#include "socket_conn.h"

enum OpCode {
	SearchOp,
	AddOp,
	RemoveOp,
	ViewOp,
	Exit
};

#define PORT	18440
#define MAXMSG	512

char buffer[MAXMSG];
struct skip_node_list local_nodes;

int read_from_client(int fd)
{
	int i, nbytes;

	char opcode;
	char *startNodeId = malloc(510*sizeof(char));
	char *qKey = malloc(510*sizeof(char));
	int level;

	nbytes = read(fd, buffer, MAXMSG);
	return nbytes;
}

void act_on_opcode() {
	char opcode;
	int node_id;
	int new_node_id;
	int key_len;
	char direction;
	char *key = malloc(100*sizeof(char));

	int buf_pos;
	int msize;
	char *mback;

	int socket_back_fd;

	buf_pos = 0;
	buf_read_char(buffer, &buf_pos, &opcode);
	switch(opcode) {
	case SearchOp:
		fprintf(stderr, "Search op received: ");
		buf_read_int(buffer, &buf_pos, &node_id);
		buf_read_int(buffer, &buf_pos, &key_len);
		buf_read_string_len(buffer, &buf_pos, &key_len, &key);
		key[key_len]='\0';
		buf_read_int(buffer, &buf_pos, &level);
		buf_read_int(buffer, &buf_pos, &source_ip);
		buf_read_int(buffer, &buf_pos, &source_port);
		assert(buf_pos==strlen(buffer));
		fprintf(stderr, "key - %s, level - %d\n", key, level);
		sg_cursor r_node = get_by_id(node_id);
		if(r_node==NULL)
			exit(1);
		if(!strcmp(r_node->data.key.name, key)) {
			buf_pos = 0;
			/* Found Opcode + key_len + key + value */
			msize = 1+4+strlen(key)+4;
			mback = (char*)malloc(msize*sizeof(char));
			buf_add_char(mback, &buf_pos, FoundOp);
			buf_add_int(mback, &buf_pos, key_len);
			buf_add_string_len(mback, &buf_pos, key_len, key);
			buf_add_int(mback, &buf_pos, value);
			assert(buf_pos==msize);

			socket_back_fd = socket_connect(source_ip, source_port);
			socket_send_message(socket_back_fd, mback);
			free(mback);
			return;
		}
		if(strcmp(r_node->data.key.name, key)<0) {
			/* Go down through the right neighbors on each level and stop at the first value greater than key */
			for( ;level>=0;level--) {
				if(!r_node->right_keys[level])
					continue;
				if(strcmp(r_node->right_keys[level], key)>0)
					break;
			}
			direction = 1;
		} else {
			for( ;level>=0;level--) {
				if(!r_node->left_keys[level])
					continue;
				if(strcmp(r_node->left_keys[level], key)<0)
					break;
			}
			direction = -1;
		}
		if(level>=0) {
			buf_pos=0;
			/* SearchOp NodeId KeyLength Key Level IP Port */
			msize = 1+4+4+strlen(key)+4+4+2; /* replace with sizeofs */
			mback = (char*)malloc(msize*sizeof(char));
			buf_add_char(mback, &buf_pos, SearchOp);
			if(direction==1)
				buf_add_int(mback, &buf_pos, r_node->right_ids[level]);
			else {
				buf_add_int(mback, &buf_pos, r_node->left_ids[level]);
				buf_add_int(mback, &buf_pos, key_len);
				buf_add_string_len(mback, &buf_pos,key_len, key);
				buf_add_int(mback, &buf_pos, level);
				buf_add_int(mback, &buf_pos, source_ip);
				buf_add_short(mback, &buf_pos, source_port);
			}
			assert(buf_pos==msize);
			if(direction==1)
				socket_back_fd = socket_connect(r_node->right_ips[level], r_node->right_pors[level]);
			else
				socket_back_fd = socket_connect(r_node->left_ips[level], r_node->left_pors[level]);
			socket_send_message(socket_back_fd, mback);
			free(mback);
			return;
		} else {
			buf_pos=0;
			/* NotFoundOp KeyLength Key */
			msize = 1+4+strlen(key);
			mback = (char*)malloc(msize*sizeof(char));
			buf_add_char(mback, &buf_pos, NotFoundOp);
			buf_add_int(mback, &buf_pos, key_len);
			buf_add_string_len(mback, &buf_pos, key_len, key);
			socket_back_fd = socket_connect(source_ip, source_port);
			socket_send_message(socket_back_fd, mback);
			free(mback);
			return;
		}
	/* LocalNodeId NewNodeId KeyLength Key Level IP Port */
	case LinkOp:
		fprintf(stderr, "Link Op: ");
		buf_read_int(buffer, &buf_pos, &node_id);
		sg_cursor r_node;
		if(r_node=snl_get_by_id(&local_nodes, node_id))
			fprintf(stderr, "with local node with key %s ", r_node->data->key.name);
		else
			return;
		buf_read_int(buffer, &buf_pos, &new_node_id);
		buf_read_int(buffer, &buf_pos, &key_len);
		buf_read_string_len(buffer, &buf_pos, &key_len, &key);
		key[key_len]='\0';
		buf_read_int(buffer, &buf_pos, &level);
		buf_read_int(buffer, &buf_pos, &source_ip);
		buf_read_short(buffer, &buf_pos, &source_port);
		fprintf(stderr, ",new key - %s, at level - %d\n", key, level, node_id);
		if(strcmp(key, r_node->data->key.name)>0) {
			r_node->right_ips[level]=source_ip;
			r_node->right_ports[level]=source_port;
			r_node->right_keys[level]=key;
			r_node->right_ids[level]=new_node_id;
		} else {
			r_node->left_ips[level]=source_ip;
			r_node->left_ports[level]=source_port;
			r_node->left_keys[level]=key;
			r_node->left_ids[level]=new_node_id;
		}
}
int main()
{
	int server_socket_fd, comm_socket_fd;
	fd_set active_fd_set, read_fd_set;
	int i;
	struct sockaddr_in clientname;
	size_t size;

	printf("Starting the skip graph server...\n");
	struct skip_graph *sg = sg_init();

	server_socket_fd = socket_open_server_socket(PORT);
	FD_ZERO(&active_fd_set);
	FD_SET(sock, &active_fd_set);

	while(1) {
		read_fd_set = active_fd_set;
		if(select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL)<0) {
			perror("ERROR selecting");
			exit(EXIT_FAILURE);
		}

		for(i=0;i<FD_SETSIZE;i++)
			if(FD_ISSET(i, &read_fd_set))
			{
				if(i==server_socket_fd)
				{
					int new;
					size = sizeof(clientname);
					new = accept(server_socket_fd, (struct sockaddr*) &clientname, &size);
					if(new<0) {
						perror("ERROR accepting");
						exit(EXIT_FAILURE);
					}
					fprintf(stderr, "Server: connect from host %s.\n", inet_ntoa(clientname.sin_addr));
					FD_SET(new, &active_fd_set);
				}
				else
				{
					if(read_from_client(i)<0)
					{
						fprintf(stderr, "socket %d closed\n", fd);
						close(i);
						FD_CLR(i, &active_fd_set);
						continue;
					}
					act_on_opcode();
				}
			}
	}
}
