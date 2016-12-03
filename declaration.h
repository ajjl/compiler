// declaration.h -- interface specificatio for parser/compiler for declarations

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established
//
// Note, the user must include "environment.h"
// before including this file

// BNF
// <declaration> ::= <identifier> : [ <private> | <restricted> ] <declarator>

#ifndef EXTERN
#define EXTERN extern
#endif

class Declaration {
public:
	static Environment * compile( Environment * e );
	// factory method?

	// =BUG= do declarations have any attributes?  they are missing here
       

private:
       //=BUG= nothing lives here yet

};

#undef EXTERN
