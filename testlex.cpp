/* testlex.c -- lexical analyzer test framework main program */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/7/2016  -- wrote main program
 */

#include <stdio.h>
#include <stdint.h>

#include "lexical.h"
#include <iostream>


#define DEBUGGING_Testlex_cpp 0

//this is a bad kludge, we should get rid of all global variables
// and all instances of extern
#define EXTERN
#include "main.h" //global variable definitions

int main(int argc, char** argv) {
	/* the main program for testlex */

	printf("argc is: %d\n", argc);
	for(int i = 0; i < argc; ++i) {
		printf("argv[%d]:\t%s\n", i, argv[i]);
	}

	lex_open( argv[1] ); /* default to stdin if argv[1] not present */

	do {
#if DEBUGGING_Testlex_cpp
		std::cout << "in a testlex loop iteration" << std::endl;
#endif
		lex_put( &lex_this, stdout );
		putchar( '\n' );  /* output each lexeme on a new line */
		lex_advance();
	} while (lex_this.type != ENDFILE);
	return 0; 
}
