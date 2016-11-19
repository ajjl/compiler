
// block.h -- interface specification for parser/compiler for blocks

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
	// factory method 

	// =BUG= blocks certainly have attributes in public section, they are missing here
private:
        //=BUG= blocks certainly have attributes in private section, they are missing here
};

//#undef EXTERN
/* comment it out, the header file now defines extern which can be used in cpp file*/


