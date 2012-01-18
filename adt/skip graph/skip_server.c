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
	opcode = buffer[0];
	switch(opcode) {
	case SearchOp:
		/* Skip whitespace after opcode */
		i = 0;
		while(*buffer!=" ")
			startNodeId[i++] = *buffer++;
		buffer++;
		i = 0;
		while(*buffer!=" ")
			qKey[i++] = *buffer++;
		buffer++;
		level = *buffer;
	

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
