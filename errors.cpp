/* errors.c -- error reporting mechanism implementation */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 * Date 9/9/2016 -- added errors raised by string pool
 */

#include <stdio.h>
#include <stdlib.h>

#define EXTERN
#include "errors.h"

/* the error messages
 * NOTE:  this array must have one entry for every
 * member of the error_message enumeration, in exactly the same order
 */
/* missing error messages like Bad command line argument, Duplicate input file name, Duplicate output file name, missing file name; and found when end of file expected, found when declaration or statement expected, found when end of block expected, found when statement expected. See exact file or error handling code through jones errors.c file in the" static const char * message[]"part, if this is something we should be worried about now. */
static const char * message[] = {
	/* intended for use in calls to error_fatal */
	/* ER_BADFILE */ "Cannot open input file.",
	/* ER_POOLOVF */ "String pool overflow.",
    /* ER_SYMTAB */ "Symbol table overflow",
	/* intended for use in calls to error_warn */
	/* ER_TOOBIG  */ "Value too large.",
	/* ER_BADSTR  */ "Unclosed string.",
	/* ER_TOOLONG */ "Identifier or string too long."
};

void error_fatal( error_message er, int line ) {
	/* output the message er and exit the program indicating failure */
	fprintf( stderr, "Fatal error on line %d: %s\n", line, message[er] );

	error_count++;
	fprintf( stderr, "Total error count: %d\n", error_count );

	exit( EXIT_FAILURE );
}

void error_warn( error_message er, int line ) {
	/* output the message er and continue */
	fprintf( stderr, "Error on line %d: %s\n", line, message[er] );
	error_count++;
}
