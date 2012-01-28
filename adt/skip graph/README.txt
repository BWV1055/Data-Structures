The skip graph is divided into skip nodes, each skip node corresponding to one piece of data (ie: one file). There can be multiple skip nodes on the same machine (as many as files added to the skip graph), each with a unique ID.
There are two special skip nodes, a start and a nil node. In order for these two nodes to exist, there has to be a server which keeps there two nodes (and also possibly its own skip nodes).

Connections between machines are made when there is some data to be sent (they are not permanent, this would cause 3*log(n) open connections per node).

Load balancing:
Currently, nodes reside on the machine they are added on. This improves manageability and security (there is no one else
who has access to the data). In the future, there will be a routing layer for load balancing.

Operations:
These are the operations available to a client:
	Add - adds a new file (specified by the filename) to the skip graph
	Remove - removes a file from the skip graph
	Search - search by name for a file and return the machine on which it resides (and possibly any value associated with the filename)
	View - list all keys in the skip graph from this machine

Internals:
Messages are passed between machines, for each message type associated with an operation there is a format:
Search:	OpCode(SearchOp) StartNodeId qKey Level
Add	  : OpCode(AddOp) StartNodeId qKey Level
Remove: OpCode(RemoveOp) StartNodeId qKey
View  : OpCode(ViewOp)
Exit  : OpCode(ExitOp)

There are a few other opcodes which are used for communication between machines, but a user cannot access them directly.

Credits:
Two ideas borrowed from https://github.com/kumagi/skip-graph :
Sending messages back to the originating node is done by appending the message originator ip and port to every subsequent message passed around.
Connections are kept open only for as long as needed (ie: they get shut down when the message is sent).
