/*
 * Auxiliarry error functions
 *
 *
 *
 */

#ifndef _MDS_ERRORS_H_
#define _MDS_ERRORS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error_codes.h"

/* Prints a message to the terminal and exits based on code */
void mds_error(uint code, const char *message, ...);
/* Returns the name of the error based on its code */
char* error_lookup(uint code);

static char **error_lookup_tbl = {
	"RESERVED",					/* 0 */
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"E_BASE_EXCEPTION",			/* 10 */
	"E_OUT_OF_RANGE",			
	"E_OUT_OF_BOUNDS",
	"E_MAX_SIZE",
	"E_ILLEGAL_STATE",	/* Operation cannot perform in this state */
	"E_ILLEGAL_ARGUMENT" /* getPrev(head) */
};



#endif
