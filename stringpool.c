/* stringpool.c -- string pool implementation */

/* Author: Douglas W. Jones
 * Date: 9/9/2016 -- initial version of implementation inferred from .h file
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "errors.h"

#define EXTERN
#include "stringpool.h"

static unsigned char string_pool[POOL_SIZE];
/* the actual location where the text of strings is stored */

static string_handle string_limit;
/* index of the first unused location in string_pool */

static string_handle string_pos;
/* position to store new characters added to string_pool */

static int string_line;
/* line number on which the string started, for error reporting */

void string_init() {
	/* initializer */
	string_limit = 1;
	/* initial value 1 guarantees that STRING_NULL won't be used */
}

string_handle string_start( int line ) {
	/* setup to accumulate a new string and return its handle */
	string_line = line;
	string_pos = string_limit + 2; /* reserve 2 bytes for string length */
	return string_limit;
}

void string_append( char ch ) {
	/* add one character to the string */
	if (string_pos > (POOL_SIZE - 1)) {
		error_fatal( ER_POOLOVF, string_line );
	}
	string_pool[string_pos] = ch;
	string_pos++;
}

void string_done() {
	/* mark the end of the string */
	int length = string_pos - (string_limit + 2);
	if (length > 65535) {
		error_warn( ER_TOOLONG, string_line );
		length = 65535;
	}
	string_pool[string_limit] = length & 0xFF;
	string_pool[string_limit + 1] = length >> 8;
}

void string_accept() {
	/* accept the string */
	string_limit = string_pos;
}

void string_reject() {
	/* reject the string, it will not be included in the string pool */
}

void string_put( string_handle h, FILE * f ) {
	/* output the string to the human-readable file */
	int limit = h + 2 + string_pool[h] + (string_pool[h + 1] << 8);
	h = h + 2;
	while (h < limit) {
		putc( string_pool[h], f );
		h = h + 1;
	}
}

/* =BUG= the code generator may need a different way to put out the string */

bool string_eq( string_handle h1, string_handle h2 ) {
	/* compare the strings h1 and h2 for textual equality */
	int limit = h1 + 2 + string_pool[h1] + (string_pool[h1 + 1] << 8);
	while (h1 < limit) {
		if (string_pool[h1] != string_pool[h2]) return false;
		h1 = h1 + 1;
		h2 = h2 + 1;
	}
	/* tricky code: since the string lengths are encoded in the first 2
	 * characters, the above loop exits early if the string lengths differ
	 */
	return true;
}
