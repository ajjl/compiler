
// block.h -- interface specificatio for parser/compiler for blocks

// Author: Douglas W. Jones
// Date 10/13/2016 -- framework established

// Note, the user must include "environment.h"
// before including this file

// BNF
// <block> ::= { <block element> [ ; ] }
// <block element> ::= <declaration> | <statement>







#ifndef EXTERN
#define EXTERN extern
#endif

class Block {
public:
	static Block * compile( Environment * e );
	// factory methid 
	// =BUG= blocks certainly have attributes, they are missing here
};
#undef EXTERN
