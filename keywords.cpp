/* keywords.h -- keyword recognition mechanism interface */

/* Author: Douglas W. Jones
 * Date: 8/23/2016 -- pasted from lecture 14 with pro-forma improved comments
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "stringpool.h"
#include "symboltable.h"

#define EXTERN
#include "keywords.h"

/* list of all the keywords in the language */
const char * const key_names[] = {
	"???", /* the null keyword handle */
	"end",          "const",        "final",        "type",
	"exception",    "var",          "procedure",    "function",
	"private",      "restricted",   "external",     "array",
	"set",          "of",           "record",       "if",
	"then",         "else",         "select",       "case",
	"while",        "do",           "until",        "for",
	"in",           "catch",        "raise",	"enum",
	"printf",	"print",	"int",		"char",
        "putstring",	"null"
};
/* IT IS CRUCIAL that the order of the strings listed in this table
 * exactly match the order of the keyword names declared in
 * key_handle in file keywords.h
 */

/* table of the symbol handles corresponding to each keyword */
symbol_handle key_table[ KEY_NULL + 1 ];

void key_init() {
	/* initializer for keyword mechanism */
        int i;
        for (i = KEY_INVALID + 1; i <= KEY_NULL; i++) {
                key_table[i] = symbol_add( key_names[i] );
        }
}

void key_put( key_handle k, FILE * f ) {
	/* output the indicated keyword to the human readable file */
        fputs( key_names[ k ], f );
}

key_handle key_lookup( symbol_handle s ) {
	/* return the keyword handle corresponding to the given symbol handle
	 * if the symbol is not a keyword, returns KEY_INVALID
	 */
	
        /* =BUG= stupid version, uses a linear search */
        int i = KEY_NULL;
        while ((i >= KEY_INVALID + 1) && (key_table[i] != s)){
		i--;
        }
	
	return (key_handle)i;
}

