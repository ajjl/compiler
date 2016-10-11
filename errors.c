/* errors.c -- error reporting mechanism implementation */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 * Date 9/9/2016 -- added errors raised by string pool
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define EXTERN
#include "errors.h"

/* the error messages
 * NOTE:  this array must have one entry for each
 * member of the error_message enumeration, in exactly the same order
 */
static const char * message[] = {
	/* intended for use in calls to error_fatal */
	/* ER_BADARG       */ "Bad command line argument",
	/* ER_EXTRAINFILE  */ "Duplicate input file name",
	/* ER_EXTRAOUTFILE */ "Duplicate output file name",
	/* ER_MISSINGFILE  */ "Missing file name",
	/* ER_BADFILE */      "Cannot open input file.",
	/* ER_POOLOVF */      "String pool overflow.",
	/* ER_SYMTAB  */      "Symbol table overflow.",
	/* intended for use in calls to error_warn */
	/* ER_TOOBIG  */      "Value too large.",
	/* ER_BADSTR  */      "Unclosed string.",
	/* ER_TOOLONG */      "Identifier or string too long.",
        /* intended for as suffixes on got-but-want messages */
	/* ER_WANT_ENDFILE */ " found when end of file expected.",
	/* ER_WANT_STATMNT */ " found when statement expected."
};

void er_help() {
	/* output the help message and exit the program */
	fprintf( stderr,
		"%s compiler [infile] [-o outfile]\n"
		"  infile defaults to standard input\n"
		"  infile = - forces input from standard input\n"
		"  outfile defaults to standard output if infile not given\n"
		"  outfile defaults i.s if infile = i.xxx\n"
		"  outfile = - forces output to standard output\n",
		main_progname
	);
}

void error_fatal( error_message er, int line ) {
	/* output the message er and exit the program indicating failure */
	fprintf( stderr, "%s: Fatal error on line %d: %s\n",
		     main_progname,              line, message[er]
	);
	exit( EXIT_FAILURE );
}

void error_warnprefix( int line ) {
	/* output the first half of a warning error for the given line */
	fprintf( stderr, "%s: Error on line %d: ",
	             main_progname,        line
	);
}

void error_warnsuffix( error_message er ) {
	/* output the second half of a warning error with the given message */
	fprintf( stderr, "%s\n",
	                  er
	);
	/* =BUG= count the number of errors so program can know at end? */
}

void error_warn( error_message er, int line ) {
	/* output the message er for line number line */
	error_warnprefix( line );
	error_warnsuffix( er );
}
