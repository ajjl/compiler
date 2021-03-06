// program.h -- interface specificatio for parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BNF
// <kestrel program> :: <block> <end of file>
#ifndef PROGRAM_H
#define PROGRAM_H


#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN int silent;

class Program {
public:
	static Program * compile();
	// factory method

	// it may well be that programs have no attributes
	// but we'll follow the standard pattern here
};

#undef EXTERN

#endif
