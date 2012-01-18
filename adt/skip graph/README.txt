This is a description of the functioning of the skip graph.

First of all, the skip graph is divided into skip nodes, each skip node corresponding to one piece of data (ie: one file). There can be multiple skip nodes on the same machine (as many as files added to the skip graph), each with a unique ID (given by hashing the filename).
There are two special skip nodes, a start and a nil node. These nodes are presumed to exist by any skip node. In order for these two nodes to exist, there has to be a server which keeps there two nodes (and also possibly its own skip nodes).

These are the operations on a skip graph:
	Add - adds a new file (specified by the filename) to the skip graph
	Remove - removes a file from the skip graph
	Search - search by name for a file and return the machine on which it resides (and possibly any value associated with the filename)
	View - list all keys in the skip graph from this machine

Messages are passed between machines, for each message type associated with an operation there is a format:
Search:	OpCode(SearchOp) StartNodeId qKey Level
Add	  : OpCode(AddOp) StartNodeId qKey Level
Remove: OpCode(RemoveOp) StartNodeId qKey
View  : OpCode(ViewOp)
Exit  : OpCode(ExitOp)

Two ideas borrowed from https://github.com/kumagi/skip-graph/
All the nodes on one machine have only one port for communication (not 3*log(n) ports per node), and sending messages back to the originating node is done by appending the message originator ip and port to every subsequent message passed around.
