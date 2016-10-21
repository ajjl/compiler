/* testlex.c -- lexical analyzer test framework main program */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/7/2016  -- wrote main program
 */

#include <stdio.h>
#include <stdint.h>

#include "lexical.h"

int main(int argc, char** argv) {
	/* the main program for testlex */

	printf("argc is: %d\n", argc);
	for(int i = 0; i < argc; ++i) {
		printf("argv[%d]:\t%s\n", i, argv[i]);
	}

	lex_open( argv[1] ); /* default to stdin if argv[1] not present */

	do {
		lex_put( &lex_this, stdout );
		putchar( '\n' );  /* output each lexeme on a new line */
		lex_advance();
	} while (lex_this.type != ENDFILE);
	return 0; 
}
