/*
 * Implementation of auxiliarry error functions
 *
 *
 */

#include "mds_errors.h"
#include <stdio.h>
#include <stdlib.h>

void mds_error(int code, const char *message, ...) {
	//parse message to see how many optional args and of what type
	va_list optional_args;
	va_start(optional_args, message);


	va_end(optional_args);
	if(code==0)
		printf("Warning: ");
	else
		printf("Error with code %d:\n", code);
	printf("%s\n", message);

	if(code)
		exit(code);
}
