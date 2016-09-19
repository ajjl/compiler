* errors.h -- error reporting mechanism interface specificaton */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 * Date 9/9/2016 -- added errors raised by string pool
 */
#ifndef ERRORS_H
#define ERRORS_H

#ifndef EXTERN
	#define EXTERN extern
#endif

typedef enum {
	/* intended for use in calls to error_fatal */
	ER_BADFILE,
	ER_POOLOVF,
	ER_SYMTAB,
	/* intended for use in calls to error_warn */
	ER_TOOBIG,
	ER_BADSTR,
	ER_TOOLONG
} error_message;

void error_fatal( error_message er, int line );
void error_warn( error_message er, int line );

#undef EXTERN
#endi

#how to detect an error once a error loop inside another, and which one comes first. 
void error_order_check(error_message er, int line);

#how to detect error message once fixed but still error
void error_re_check(error_message er, int line);

