// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BN
/*not quite understand this yet about the standard environmrnt part, is this about the gcc compiler environment or our CMake is already included in this, otherwise should we include #iostream in this file or just be sure that #iostreamt is always included in other files this program called is OK? or this bug ntice of must create standard environment is already solved? Hopefully someone can help me out*/
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

	Environment * e = NULL;
	// =BUG= must create standard environment e

	// =BUG= must call code generator to putput standard prefix

	Block * b = Block::compile( e );

	// =BUG= must call code generator to output standard suffix

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDFILE);

	return NULL;
}
