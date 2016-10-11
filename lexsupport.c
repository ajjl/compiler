/* lexsupport.c -- lexical analyzer support package implementation */

/* Author: Douglas W. Jones
 * Date 8/19/2016 -- pasted from Lecture 12 with pro-forma improved comments
 */

#include <stdint.h>
#include <stdio.h>
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
}

/* bool lex_iskey( lexeme lex, key_type t ) { */ /* =BUG= finish this */

/* bool lex_iskeyset( lexeme lex, set32_t s ) */
/* implemented in header file */

bool lex_gotbutwant( lexeme lex, error_message e ) {
	/* error: this lexeme e, where e is typically found when x expected */
	error_warnprefix( lex.line );
	lex_put( lex, stderr ); 
	error_warnsuffix( e );
}

void lex_wantinset( set32_t ps, set32_t ks, set32_t ls, error_message e ) {
	/* force lex_this to be in one of the sets or gotbutwant e */
	/* typically used to force lex_this into start set or follow set  */

	if (lex_ispuncset( lex_this, ps )) return;
	if (lex_iskeyset( lex_this, ks )) return;
	if (in_set32( lex_this.type, ls )) return;
	lex_gotbutwant( lex_this, e );
}