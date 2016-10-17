// statement.h -- interface specificatio for parser/compiler for statements

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established
//
// Note, the user must include "environment.h"
// before including this file

// BNF
// <statement> ::= <if> | <case> | <for loop> | <while loop> | <do loop>
//              |  <exception handler> | <raise> | <procedure call>
//              |  <assignment>
// this grammar splits <loop> and folds <do end> into <do loop>

#ifndef EXTERN
	#define EXTERN extern
#endif

class Statement {
public:
	static Statement * compile( Environment * e );
	// factory method

	// =BUG= do statements have any attributes?  they are missing here
};

#undef EXTERN
