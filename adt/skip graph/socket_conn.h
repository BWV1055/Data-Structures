/*
 *	Open/close an Internet domain TCP type connection
 */

/* Returns the file descriptor for a new server socket 
 * Ports used are in the range 18440 - 18450 */
int socket_open_server_socket(int port) {
	int server_socket_fd;
	struct sockaddr_in serv_addr;
	if(port<18440 || port>=18450)
		return;
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = port;
	serv_addr.sin_addr = INADDR_ANY;
	server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket_fd<0)
		error("ERROR opening socket");
	if(bind(server_socket_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)
		error("ERROR on binding");
	listen(server_socket_fd, 5);
	return server_socket_fd;
}
/* Listens for a new connection request from a client and creates a file descriptor
 * when such a request appears */
int socket_server_accept(int server_socket_fd) {
	int comm_socket_fd;
	struct sockaddr_in cli_addr;
	comm_socket_fd = accept(server_socket_fd, (struct sockaddr*) &cli_addr, sizeof(cli_addr));
	if(comm_socket_fd<0)
		error("ERROR on accept");
	return comm_socket_fd;
}
/* Client connects to server and returns the socket_fd for this connection */
int socket_connect(char *hostname, int port) {
	int socket_fd;
	struct hostent *server;
	struct sockaddr_in serv_addr;

	server = gethostbyname(hostname);
	if(server==NULL)
		error("Could not locate %s\n", hostname);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(socket_fd, &serv_addr, sizeof(serv_addr)<0))
		error("ERROR connecting");
	return socket_fd;
}
	

/* Reads a new message from the comm_socket_fd
 * And call appropriate function based on the received code 
 * Both client and server use this function */
void socket_read_message(int comm_socket_fd) {
	int i;
	char *buffer, *it;
	char *opcode, *key;
	struct skip_node *start;
	bzero(buffer, 256);
	if(read(comm_socket_fd, buffer, 255)<0)
		error("ERROR reading from socket");
	/* For debug purposes */
	printf("Received message: %s\n", buffer);
	it = buffer;
	i=0;
	while(*(it+i)!=0x10)
		opcode[i] = it[i++];
	opcode[i]='\0';	
	it++;
	start = it;
	i=0;
	while(*(it+i)!='\0')
		key[i] = it[i++];
	if(opcode=='search')
		printf("Search op received\n");
}

void socket_send_message(int comm_socket_fd, char op, struct skip_node *cur, key_t qKey) {
	char *message = malloc(256*sizeof(char));
	message[0] = op;
	message[1] = 0x10;
	message[2] = cur;
	memcpy(message[3], qKey.name, strlen(qKey.name));
	if(write(comm_socket_fd, message, strlen(message))<0)
		error("ERROR writing to socket");
	
}
