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
	ER_TOOLONG
} error_message;

void er_help();
/* output the help message and exit the program */

void error_fatal( error_message er, int line );
void error_warn( error_message er, int line );

#undef EXTERN
