// statement.cpp -- implementation of parser/compiler for statements

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established

// BNF
// <statement> ::= <if> | <case> | <for loop> | <while loop> | <do loop>
//              |  <exception handler> | <raise> | <procedure call>
//              |  <assignment>
// this grammar splits <loop> and folds <do end> into <do loop>

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

#define EXTERN
#include "statement.h"

// =BUG= code to compile <if> <case> <for loop> <while loop> <do loop>
// =   =                 <exception handler> <raise> <procedure call>
// =   =                 <assignment>
// =   = could all go here as local classes, not in the header file
// =   = but if they start getting big and unwieldy, they can each
// =   = be put in ther own files

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
		   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
		   )
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
		    | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL ) \
		    )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )

Statement * Statement::compile( Environment * e ) {

	lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_STATE );

	// =BUG= big kluge!! statement stub just eats one lexeme
	lex_advance();

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_BLOCK );

	// =BUG= do statements need to return any attributes?
	return NULL;
}
