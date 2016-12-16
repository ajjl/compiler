// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BNF
// <kestrel program> ::=  <block> <end of file>

#include <stdint.h>
#include <stdio.h>
#include "sets.h"
#include "errors.h"
#include "lexical.h"
#include "lexsupport.h"
#include "ExplodingTeeth.h"

#include "environment.h"
#include "block.h"

#define EXTERN
#include "program.h"

/* follow set for programs */
#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS SET32_EMPTY
#define FOLLOW_LEXS to_set32( ENDFILE )
Program * Program::compile() {

	Environment * e = new Environment(NULL);  //The first environment has no parent

	// =BUG= standard prefix for code generator needed

    std::cout << "#Start" << std::endl;
	Block * b = Block::compile( e );


    // Print proloug and epilog
    int bigOffset = e->getBigOffset();
    std::cout << "#Proloug" << std::endl;
    generate_prolog(bigOffset);
    std::cout << "#Epilog " << std::endl;
    generate_epilog(bigOffset);
	// =BUG= standard suffix for code generator needed

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDFILE);

	return NULL;
}
