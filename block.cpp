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
#include "ExplodingTeeth.h"

#include "environment.h"
#include "declaration.h"
#include <iostream>
#include <cstdio>
#include "statement.h"

// #define EXTERN
// if we ever have global var in block.h, then we will need to un comment the above line

#include "block.h"

#define Debugging_block 0


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
#if Debugging_block
    std::cout << "in Block::Compile" << std::endl;
    std::cout << "Environment is : " << e << std::endl;
	char message[300] ;
	std::sprintf(message, "value of lexeme in, %s: %d",__FILE__,  __LINE__);
    lex_this.print_lex(message);
#endif

	lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_BLOCK );

	while (lex_isinset( START_PUNCS, START_KEYS, START_LEXS )) {
#if Debugging_block
		std::cout << "in whileloop of Block::Compiler" << std::endl;
		lex_this.print_lex();
#endif

		if ( (lex_this.type == IDENT)
		&&   lex_ispunc( lex_next, PT_COLON ) ) { //checking to see if assignment/declaration
			// all declarations begin with ident:
#if Debugging_block
			std::cout << " I think I'm a declaration." << std::endl;
#endif
			e = Declaration::compile( e );
		} else  {
			// if it is a statement

			#if Debugging_block
			std::cout << " I think I'm a statement." << std::endl;
			std::cout << " Environment before: " << std::endl;
			e->print();
			#endif

			Statement * s = Statement::compile( e );

			#if Debugging_block
			std::cout << " Environment after: " << std::endl;
			e->print();
			#endif

		}
		if (lex_ispunc( lex_this, PT_SEMI )){
#if Debugging_block
   			std::cout << "this is the end of the current block::Compile"<< std::endl;
#endif
                	lex_advance();
		}

            
	/* if lex_this is a SEMI, this is the end of block.*/
   
}

int bigOffset = e->getBigOffset();
std::cout << "#Proloug" << std::endl;
generate_prolog(bigOffset);
std::cout << "#Epilog " << std::endl;
generate_epilog(bigOffset);
#if Debugging_block
	std::cout << "after whileloop of Block::Compile"<< std::endl;
#endif

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDBLOK);

#if Debugging_block
    std::cout << "End of Block::Compile" << std::endl;
#endif
	return NULL;
}

