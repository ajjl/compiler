/* errors.h -- error reporting mechanism interface specificaton */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 * Date 9/9/2016 -- added errors raised by string pool
 * Date 9/12/2016 -- added errors raised by symbol table
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

typedef enum {
	/* intended for use in calls to error_fatal */
	ER_BADARG,
	ER_EXTRAINFILE,
	ER_EXTRAOUTFILE,
	ER_MISSINGFILE,
	ER_BADFILE,
	ER_POOLOVF,
	ER_SYMTAB,
	/* intended for use in calls to error_warn */
	ER_TOOBIG,
	ER_BADSTR,
	ER_TOOLONG,
	/* intended for as suffixes on got-but-want messages */
	ER_WANT_ENDFILE,
	ER_WANT_STATMNT,
} error_message;

void er_help();
/* output the help message and exit the program */

void error_fatal( error_message er, int line );
/* output the message er and exit the program indicating failure */

void error_warnprefix( int line );
/* output the first half of a warning error for the given line */

void error_warnsuffix( error_message er );
/* output the second half of a warning error with the given message */

void error_warn( error_message er, int line );
/* output the message er for line number line
 * note, this is just the prefix followed by the suffix
 * these may be split to create "error x found but y expected" messages
 */

#undef EXTERN
