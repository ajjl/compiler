// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established
//parsing starts here
// BNF
// <kestrel program> ::=  <block> <end of file>

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
//need to check if it is a valid program to compile
//check for if the first element is a block element or not
//and if the final contains the end-of-file sign if applicable
Program * Program::compile() {

	Environment * e = new Environment(NULL);  //The first environment has no parent

	// =BUG= standard prefix for code generator needed
         
	Block * b = Block::compile( e );

	// =BUG= standard suffix for code generator needed

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDFILE);

	return NULL;
}
