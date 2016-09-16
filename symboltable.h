/* symboltable.h -- symbol table interface specification */

/* Author: Douglas W. Jones
 * Date: 9/12/2016 -- initial version of interface, from Lecture 9
 */

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdio.h>
#include <stdbool.h>
/*
 * users of this file must first include
 * users should define (probably from a global config file)
 *   SYMBOL_SIZE -- how many distinct symbols are allowed
 *   SYMBOL_HASH -- used in the hash function, relatively prime to SYMBOL_SIZE
 * when used from symboltable.c (but nowhere else)
 *   first define EXTERN as nothing.
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

typedef uint32_t symbol_handle;
/* the symbol handle type.  C and C++ don't let us say so, but
 * the value is between 0 and SYMBOL_SIZE-1, inclusive.
 */

EXTERN unsigned char _symbol_table[SYMBOL_SIZE];
/* private, the actual location where the text of strings is stored */

EXTERN symbol_handle _symbol_hash;
/* private, used to accumulate the hash of the symbol */

EXTERN string_handle _symbol_string;
/* private, tentative handle for the string being accumulated */

EXTERN int _symbol_line;
/* private, used for error reporting, the line from which the symbol came */

void symbol_init();
/* initialize the symbol table */

/* string_handle symbol_start( int line ); */
#define symbol_start(line) {				\
	_symbol_hash = 0;				\
	_symbol_string = string_start( line );		\
	_symbol_line = line;				\
}
/* setup to accumulate a new symbol, from given line (for error reporting) */

/* void symbol_append( char ch ); */
#define symbol_append(ch) {				\
	_symbol_hash = ((_symbol_hash * SYMBOL_HASH )	\
			+ (ch)) % SYMBOL_SIZE;		\
	string_append(ch);				\
}
/* add one character to the symbol */

symbol_handle symbol_lookup();
/* mark the end of the symbol and return its handle */

/* note:
 * to add a symbol
 *   symbol_start( current_line )
 *   for each character ch in symbol { symbol_append( ch ) }
 *   handle = symbol_lookup()
 */

/* void symbol_put( symbol_handle h, FILE * f ); */
#define symbol_put(h,f) string_put( _symbol_table[h], f )
/* output the text of the symbol to the human-readable file */

/* =BUG= the code generator may need a different way to put out the symbol */

#undef EXTERN
#endif
