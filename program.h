// program.h -- interface specificatio for parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established
//
// Note, the user must include <stdint.h> and "sets.h"
//       before including this file

// BNF
// <kestrel program> :: <block> <end of file>

#ifndef EXTERN
	#define EXTERN extern
#endif

class Program {
public:
	static Program * compile();
	// factory method

	// it may well be that programs have no attributes
	// but we'll follow the standard pattern here
};

#undef EXTERN
