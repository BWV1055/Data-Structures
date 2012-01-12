/*
 * Error codes, which should actually be called exception codes
 * 	See http://www.haskell.org/haskellwiki/Error_vs._Exception
 * For each code, in the description, there is an example of when 
 * 	it should be used
 * The basic idea is that higher error codes appear only in more complex
 *  data structures, while codes with a lower value belong mostly to
 *	simpler data structures.
 *
 * Ranges:
 * 	 0 - 9    Reserved
 * 	10 - 30   General, array and linked list
 * 	31 - 40   Stack and queue
 * 	41 - 50   Reserved
 * 	51 - 60   Trees (all)
 * 	61 - 70   Priority queue
 * 	71 - 80   Unordered maps
 * 	81 - 90   Ordered maps
 * 	91 - 110  Search trees
 * 111 - 120  Sorting and text searches
 *
 */

#ifndef _ERROR_CODES_H_
#define _ERROR_CODES_H_

/* General error code, when there is no specific code defined */
#define E_BASE_EXCEPTION			10
#define E_OUT_OF_RANGE				11
#define	E_OUT_OF_BOUNDS				12
#define E_MAX_SIZE					13
#define E_ILLEGAL_STATE				14
#define E_ILLEGAL_ARGUMENT			15

/* st_push() is stack is full */
#define E_EMPTY_STACK				31
/* st_pop() is stack is empty */
#define E_FULL_STACK				32
/* tr_insert() with non existent path */
#define E_INVALID_POSITION			51
/* tr_parent() called on root */
#define E_BOUNDARY_VIOLATION		52
/* tr_root() called on an empty tree */
#define E_EMPTY_TREE				53

#endif
