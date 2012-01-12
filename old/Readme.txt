These data structures present to the ADTs as many functions as possible and let them choose which functions to use.




TODO: 
 - Define a common set of functions that linked lists should implement, and special functions for doubly linked lists and circularly linked list.
 - Finish circularly linked list and resizable array and test them with test_bds.c.
 - Make singly linked list self-organizing (http://en.wikipedia.org/wiki/Self-organizing_list), and set a flag to choose this option
 - For each data structure, in the header, specify the time (or space) for: insert/remove at beginning, end, middle, random access, wasted space, search



Distant future:
Self-healing data-structure:
	let it be punctured by new insertions (ie: break a contiguous array into two nodes, plus a new node in-between), and from time to time, use something similar to CDR lists to create a contiguous area (call the link-patcher to recreate an array from multiple nodes).
