// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BN
/*not quite understand this yet about the standard environmrnt part, is this about the gcc compiler environment or our CMake is already included in this, otherwise should we include #iostream in this file or just be sure that #iostreamt is always included in other files this program called is OK? or this bug ntice of must create standard environment is already solved? Hopefully someone can help me out*/
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
