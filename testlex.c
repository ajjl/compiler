/* testlex.c -- lexical analyzer test framework main program */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/7/2016  -- wrote main program
 */

#include <stdio.h>
#include <stdint.h>

#include "lexical.h"

main() {
	/* the main program for testlex */

	/* =BUG= this should open argv[1] if present so we can read files */
	lex_open( NULL ); /* default to stdin if argv[1] not present */
	do {
		lex_put( &lex_this, stdout );
		putchar( '\n' ); /* output each lexeme on a new line */
		lex_advance();
	} while (lex_this.type != ENDFILE);
}
