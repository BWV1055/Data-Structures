/*
 * Error codes, which should actually be called exception codes
 * For each code there is one example when it should be used
 *
 */

#ifndef _ERROR_CODES_H_
#define _ERROR_CODES_H_

/* st_push() is stack is full */
#define E_OVERFLOW				1
/* st_pop() is stack is empty */
#define E_UNDERFLOW				2
/* tr_insert() with non existent path */
#define E_INVALID_POSITION		3
/* tr_parent() called on root */
#define E_BOUNDARY_VIOLATION	4
/* tr_root() called on an empty tree */
#define E_EMPTY_TREE			5

#endif
