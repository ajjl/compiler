// declaration.cpp -- implementation of parser/compiler for declarations

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established

// BNF
// <declaration> ::= <identifier> : [ <private> | <restricted> ] <declarator>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "sets.h"
#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"

#define EXTERN
#include "declaration.h"

#define Debugging_declaration 1

// =BUG= code to compile various kinds of declarations might
// =   = go here as local classes, not in the header file
// =   = but if they start getting big and unwieldy, they can each
// =   = be put in ther own files

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS SET32_EMPTY
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
		    | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL ) \
		    )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )

Environment * Declaration::compile( Environment * e ) {
	std::cout << "in Decleration::compile" << std::endl;

	// lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_??? );
	// the above is not needed because Block::compile() is the only caller
	// and it only calls this code when it sees <identifier>:

	// =BUG= we should put the identifier in the environment
	std::cout << "PRINTING ELEMENTS" << std::endl;
	e->addElement(lex_this.value, 0);

	#if Debugging_declaration
	// e -> printAll();
	#endif

	#if Debugging_declaration
	lex_this.print_lex();
	#endif
	lex_advance(); // skip identifier

	#if Debugging_declaration
	lex_this.print_lex();
	#endif
	lex_advance(); // skip colon

	#if Debugging_declaration
	lex_this.print_lex();
	#endif
	// =BUG= we should do something about private and restricted keywords
	lex_advance(); // this one skips "var" or whatever

	#if Debugging_declaration
	lex_this.print_lex();
	#endif
	// =BUG= big kluge!  Stub to skip over the minimal declaration
	lex_advance(); // this is skipping "int" or the type of the var
	// skipping everything because the current version only supports ints


	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_BLOCK );

	// =BUG= we should return a useful environment
	#if Debugging_declaration
	std::cout << "end of Declaration::Compile" << std::endl;
	#endif

	return e;
}
