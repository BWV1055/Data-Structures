/*
 * Definition of structs and data types
 *	Also, macros for comparing two values
 *
 *
 *
 */

#ifndef	_MDS_DATA_TYPES_H_
#define	_MDS_DATA_TYPES_H_

#include <sys/types.h>

#define G_DATA_FLAG_READ		(1<<0)
#define G_DATA_FLAG_WRITE		(1<<1)
#define G_DATA_FLAG_EXECUTE		(1<<2)

typedef unsigned char uchar_t;
typedef unsigned int uint_t;

/* One special data type, the position ADT 
 *	It has only one method, which returns the value stored at that position
 *	This method is implemented using dereferencing and returning the data field:
 * 		*cursor.data	*/

typedef void*	position;

typedef struct {
	void *ptrData;
	size_t size;
	uchar_t type;
	uchar_t flags;
} generic_data_t;

typedef struct {
	generic_data_t key;
	generic_data_t value;
} assoc_pair_data_t;

typedef void(*function_t)(void);

typedef struct {
	assoc_pair_data_t *members;
	size_t sMembers;
	function_t *functions;
	size_t sFunctions;
	uchar_t flags;
} class_data_t;

typedef struct {
	char *name;
	size_t len;
} key_t;

/* A very simple generic data structure, used in most data structures */
struct generic_data {
	key_t key;
	int value;
};

#include <string.h>

#define G_DATA_MIN						0x00
#define G_DATA_MAX						0xff

#define G_DATA_CMP(a,b)					strcmp(a.key.name, b.key.name)

#define G_DATA_EQUAL(a,b)				(G_DATA_CMP(a,b) == 0)
#define G_DATA_GREATER(a,b)				(G_DATA_CMP(a,b) > 0)
#define G_DATA_GREATER_OR_EQUAL(a,b)	(G_DATA_CMP(a,b) >= 0)


#endif
