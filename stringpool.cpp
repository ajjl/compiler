/* stringpool.c -- string pool implementation */

/* Author: Douglas W. Jones
 * Date: 9/9/2016 -- initial version of implementation inferred from .h file
 * Date: 9/12/2016 -- supports fast interface from Lecture 9
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "errors.h"

#define EXTERN
#include "stringpool.h"

/* static unsigned char string_pool[POOL_SIZE]; */
/* declaration moved to stringpool.h */

/* static string_handle string_limit; */
/* declaration moved to stringpool.h */

/* static string_handle string_pos; */
/* declaration moved to stringpool.h */

/* static int string_line; */
/* declaration moved to stringpool.h */

/* void string_init() { */
/* code moved to stringpool.h */

/* string_handle string_start( int line ) { */
/* code moved to stringpool.h */

/* void string_append( char ch ) { */
/* code moved to stringpool.h */

/* void string_done() { */
/* code moved to stringpool.h */

/* void string_accept() { */
/* code moved to stringpool.h */

/* void string_reject() { */
/* code moved to stringpool.h */

void string_put( string_handle h, FILE * f ) {
	/* output the string to the human-readable file */
	string_handle limit = h + 2 + _string_pool[h] + (_string_pool[h + 1] << 8);

	h = h + 2;

	while (h < limit) {
		putc( _string_pool[h], f );
		h = h + 1;
	}
}

/* =BUG= the code generator may need a different way to put out the string */

bool string_eq( string_handle h1, string_handle h2 ) {
	/* compare the strings h1 and h2 for textual equality */
	string_handle limit = h1 + 2 + _string_pool[h1] + (_string_pool[h1 + 1] << 8);
	while (h1 < limit) {
		if (_string_pool[h1] != _string_pool[h2]) return false;
		h1 = h1 + 1;
		h2 = h2 + 1;
	}
	/* tricky code: since the string lengths are encoded in the first 2
	 * characters, the above loop exits early if the string lengths differ
	 */
	return true;
}
