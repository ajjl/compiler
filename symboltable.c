/* symboltable.c -- symbol table implementation */

/* Author: Douglas W. Jones
 * Date: 9/12/2016 -- initial version of interface, from Lecture 9
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
/* this defines
 *   SYMBOL_SIZE -- how many distinct symbols are allowed
 *   SYMBOL_HASH -- used in hash function, relatively prime to SYMBOL_SIZE
 */
#include "errors.h"
#include "stringpool.h"

#define EXTERN
#include "symboltable.h"

/* static unsigned char _symbol_table[SYMBOL_SIZE]; */
/* declared in symboltable.h */

/* static symbol_handle _symbol_hash; */
/* declared in symboltable.h */

/* static string_handle _symbol_string; */
/* declared in symboltable.h */

/* static int _symbol_line; */
/* declared in symboltable.h */

void symbol_init() {
	/* initialize the symbol table */
	symbol_handle i;
	for (i = 0; i < SYMBOL_SIZE; i++) _symbol_table[i] = STRING_NULL;
}

/* string_handle symbol_start( int line ); */
/* implemented in symboltable.h */

/* void symbol_append( unsigned char ch ); */
/* implemented in symboltable.h */

symbol_handle symbol_lookup() {
	/* mark the end of the symbol and return its handle */
	string_done();
	symbol_handle place = _symbol_hash;
	for (;;) { /* loop exits by embedded returns */
		if (_symbol_table[place] == STRING_NULL ) {
			/* add symbol to table */
			_symbol_table[place] = _symbol_string;
			string_accept();
			return place;
		}
		if (string_eq( _symbol_table[place], _symbol_string )) {
			/* symbol is already in table */
			string_reject();
			return place;
		}
		/* circular increment */
		place = place + 1;
		if (place == SYMBOL_SIZE) place = 0;

		/* if we get back to our starting point, trouble */
		if (place == _symbol_hash) {
			error_fatal( ER_SYMTAB, _symbol_line );
		}
	}
}

/* note:
 * to add a symbol
 *   symbol_start( current_line )
 *   for each character ch in symbol { symbol_append( ch ) }
 *   handle = symbol_lookup()
 */

/* void symbol_put( symbol_handle h, FILE * f ); */
/* implemented in symboltable.h */

/* =BUG= the code generator may need a different way to put out the symbol */
