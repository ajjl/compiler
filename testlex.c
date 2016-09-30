/* testlex.c -- lexical analyzer test framework main program */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/7/2016  -- wrote main program
 * Date 9/30/2016  -- make it compatible with main.c from Kestrel compiler
 */

#include <stdio.h>
#include <stdint.h>

#include "config.h"
#include "lexical.h"

#define EXTERN
#include "main.h"

main() {
	/* the main program for testlex */
	main_progname = DEFAULT_NAME;

	/* =BUG= this should open argv[1] if present so we can read files */
	lex_open( NULL ); /* default to stdin if argv[1] not present */
	do {
		lex_put( &lex_this, stdout );
		putchar( '\n' ); /* output each lexeme on a new line */
		lex_advance();
	} while (lex_this.type != ENDFILE);
}
