/* lexsupport.c -- lexical analyzer support package implementation */

/* Author: Douglas W. Jones
 * Date 8/19/2016 -- pasted from Lecture 12 with pro-forma improved comments
 */

#include <stdint.h>
#include "lexical.h"
#include "sets.h"

#define EXTERN
#include "lexsupport.h"

/* bool lex_ispunc( lexeme lex, punct_type t ) { */
/* implemented in header file */

/* bool lex_ispuncset( lexeme lex, set32_t s ) { */
/* implemented in header file */

bool lex_forcepunc( punct_type t ) {
	/* force lex_this to be the punctuation mark t and advance over it */
	if (lex_ispunc( lex_this, t )) {
		lex_advance();
	} else {
		/* =BUG= must report that we found lex_this where t expected */
	}
	printf("This function in: %s, line: %d, is not yet fully implemented.", __FILE__, __LINE__);
}
