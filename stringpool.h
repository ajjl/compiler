/* stringpool.h -- string pool interface specification */

/* Author: Douglas W. Jones
 * Date: 9/9/2016 -- initial version of interface
 */

/* users of this file must first include
 *   <stdio.h>
 *   <stdint.h>
 *   <stdbool.h>
 * users should define (probably from a global config file)
 *   POOL_SIZE -- how much space should be set aside for text of strings
 * when used from stringpool.c (but nowhere else)
 *   first define EXTERN as nothing.
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

typedef uint32_t string_handle;
/* the string handle type.  C and C++ don't let us say so, but
 * the value is between 0 and POOL_SIZE-1, inclusive.
 */

#define STRING_NULL 0
/* the null string handle, refers to no string */

void string_init();
/* initializer */

string_handle string_start( int line );
/* setup to accumulate a new string, from given line (for error reporting) */

void string_append( char ch );
/* add one character to the string */

void string_done();
/* mark the end of the string */

void string_accept();
void string_reject();
/* accept or reject the string.  If rejected, it is not stored */

/* note:
 * to add a string to the pool
 *   handle = string_start( current_line )
 *   for each character ch in string { string_append( ch ) }
 *   string_done()
 *   either string_accept() or string_reject() -- symboltable's decision
 */

void string_put( string_handle h, FILE * f );
/* output the text of the string to the human-readable file */

/* =BUG= the code generator may need a different way to put out the string */

bool string_eq( string_handle h1, string_handle h2 );
/* compare the strings h1 and h2 for textual equality */

#undef EXTERN
