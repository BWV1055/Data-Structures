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
	int key_len;
	char *key = malloc(100*sizeof(char));

	int buf_pos = 0;
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
			int buf_pos = 0;
			/* Found Opcode + key_len + key + value */
			int msize = 1+4+strlen(key)+4;
			char *mback = (char*)malloc(msize*sizeof(char));
			buf_add_char(mback, &buf_pos, FoundOp);
			buf_add_int(mback, &buf_pos, key_len);
			buf_add_string_len(mback, &buf_pos, key_len, key);
			buf_add_int(mback, &buf_pos, value);
			assert(buf_pos==msize);

			int socket_back_fd = socket_connect(source_ip, source_port);
			socket_send_message(socket_back_fd, mback);
			return;
		}
		if(strcmp(r_node->data.key.name, key)>0) {



		} else {




		}

		


	case AddOp:
		
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
