// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BNF
// <kestrel program> :: <block> <end of file>

#include <stdint.h>
#include <stdio.h>
#include "sets.h"
#include "errors.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"
#include "block.h"

#define EXTERN
#include "program.h"

/* follow set for programs */
#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS SET32_EMPTY
#define FOLLOW_LEXS to_set32( ENDFILE )

Program * Program::compile() {

	Environment * e = new Environment(NULL);  //The first environment has no parent

	// =BUG= must call code generator to putput standard prefix

	Block * b = Block::compile( e );

	// =BUG= must call code generator to output standard suffix

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDFILE);

	return NULL;
}
