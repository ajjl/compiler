/* stringpool.h -- string pool interface specification */

/* Author: Douglas W. Jones
 * Date: 9/9/2016 -- initial version of interface
 * Date: 9/12/2016 -- supports fast interface from Lecture 9
 */

#ifndef STRINGPOOL_H
#define STRINGPOOL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "errors.h"
#include "config.h"

/*
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

EXTERN unsigned char _string_pool[POOL_SIZE];
/* private, the actual location where the text of strings is stored */

EXTERN string_handle _string_limit;
/* private, the address of the next unused location in the pool */

EXTERN string_handle _string_pos;
/* private, used in accumulating a new string (provisionally) */

EXTERN int _string_line;
/* private, used for error reporting, the line from which the string came */

/* void string_init(); */
#define string_init() { _string_limit = 1; }
/* initializer */

inline
string_handle string_start(int line) {
	_string_line = line;
	_string_pos = _string_limit + 2;
	return _string_limit;
}
/* setup to accumulate a new string, from given line (for error reporting) */

inline
void string_append( char ch ) {
	if (_string_pos > (POOL_SIZE - 1)) {
		error_fatal( ER_POOLOVF, _string_line );
	}
	_string_pool[_string_pos] = ch;
	_string_pos++;
}
/* add one character to the string */

inline
void string_done() {
	int length = _string_pos - (_string_limit + 2);
	if (length > 65535) {
		error_warn( ER_TOOLONG, _string_line );
		length = 65535;
	}
	_string_pool[_string_limit] = length & 0xFF;
	_string_pool[_string_limit + 1] = length >> 8;
}
/* mark the end of the string */

/* void string_accept(); */
#ifndef string_accept
#define string_accept() { _string_limit = _string_pos; }
#endif
/* accept the new string, it is permanently in the string pool */

/* void string_reject(); */
#ifndef string_reject
#define string_reject() {_string_limit = 0;}
#endif
/*should there be something else above to the string_reject?*/

/* reject the new string, recover the space in the stirng pool */

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
#endif
