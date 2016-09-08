/* errors.c -- error reporting mechanism implementation */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 */

#include <stdio.h>
#include <stdlib.h>

#define EXTERN
#include "errors.h"

/* the error messages
 * NOTE:  this array must have one entry for each
 * member of the error_message enumeration, in exactly the same order
 */
static const char * message[] = {
	/* intended for use in calls to error_fatal */
	/* ER_BADFILE */ "Cannot open input file.",
	/* intended for use in calls to error_warn */
	/* ER_TOOBIG  */ "Value too large."
};

void error_fatal( error_message er, int line ) {
	/* output the message er and exit the program indicating failure */
	fprintf( stderr, "Fatal error on line %d: %s\n", line, message[er] );
	exit( EXIT_FAILURE );
}

void error_warn( error_message er, int line ) {
	/* output the message er and continue */
	fprintf( stderr, "Error on line %d: %s\n", line, message[er] );
	/* =BUG= count the number of errors so program can know at end? */
}
