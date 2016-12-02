#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "sets.h"
#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"
#include "declaration.h"
#include <iostream>
#include <cstdio>
#include "statement.h"

//#define EXTERN8
/*Why do we need to define EXTERN in this part, which has already defined in the header file*/

#include "block.h"

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
		   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
		   )
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL )
#define FOLLOW_LEXS to_set32( ENDFILE )

#include <iostream>
// internal sets

Block * Block::compile( Environment * e ) {
    std::cout << "in Block::Compile" << std::endl;
    std::cout << "Environment is : " << e << std::endl;
	char message[300] ;
	std::sprintf(message, "value of lexeme in, %s: %d",__FILE__,  __LINE__);
    lex_this.print_lex(message);

	lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_BLOCK );

	while (lex_isinset( START_PUNCS, START_KEYS, START_LEXS )) {
		std::cout << "in whileloop of Block::Compiler" << std::endl;
		lex_this.print_lex();

		if ( (lex_this.type == IDENT)
		&&   lex_ispunc( lex_next, PT_COLON ) ) { //checking to see if assignment/declaration
			// all declarations begin with ident:
			std::cout << " I think I'm a declaration." << std::endl;
			e = Declaration::compile( e );
		} else {
			// if not a declaration must be a statement
			std::cout << " I think I'm a statement." << std::endl;
			Statement * s = Statement::compile( e );
		}
		if (lex_ispunc( lex_this, PT_SEMI )) lex_advance();
	}
	std::cout << "after whileloop of Block::COmpile"<< std::endl;

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDBLOK);

	// =BUG= the following is almost certainly an error
    std::cout << "End of Block::Compile" << std::endl;
	return NULL;
}

