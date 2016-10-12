// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BNF
// <kestrel program> :: <block> <end of file>

#include <stdint.h>
#include "sets.h"
#include "errors.h"
#include "lexical.h"
#include "block.h"

#define EXTERN
#include "program.h"

Program::compile() {

	// =BUG= must create standard environment e

	Block b = Block::compile( e );

	lex_wantinset( 0, 0, to_set32( ENDFILE ), ER_WANT_ENDFILE );
}
