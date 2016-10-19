st login: Wed Oct 19 16:21:41 on ttys000
HONGXUs-MacBook-Pro:~ hongxuli$ cd jones
HONGXUs-MacBook-Pro:jones hongxuli$ svn update
Updating '.':
U    block.h
A    statement.cpp
A    statement.h
U    errors.c
U    errors.h
U    lexical.c
U    main.cpp
U    lexsupport.c
A    declaration.cpp
U    lexical.h
U    lexsupport.h
A    declaration.h
U    block.cpp
U    Makefile
Updated to revision 312.
HONGXUs-MacBook-Pro:jones hongxuli$ vi statement.cpp
HONGXUs-MacBook-Pro:jones hongxuli$ vi statement.cpp























HONGXUs-MacBook-Pro:jones hongxuli$ vi statement.h
HONGXUs-MacBook-Pro:jones hongxuli$ ls
Makefile        declaration.h   lexical.c       program.cpp     stringpool.h
README          environment.h   lexical.h       program.h       symboltable.c
block.cpp       errors.c        lexsupport.c    sets.h          symboltable.h
block.h         errors.h        lexsupport.h    statement.cpp   testlex.c
config.h        keywords.c      main.cpp        statement.h
declaration.cpp keywords.h      main.h          stringpool.c
HONGXUs-MacBook-Pro:jones hongxuli$ vi declaration.cpp
HONGXUs-MacBook-Pro:jones hongxuli$ vi block.cpp

// block.cpp -- implementation of parser/compiler for blocks

// Author: Douglas W. Jones
// Date 10/12/2016 -- framework established

// BNF
// <block> ::= { <block element> [ ; ] }
// <block element> ::= <declaration> | <statement>

#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "sets.h"
#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"
#include "declaration.h"
#include "statement.h"

#define EXTERN
#include "block.h"

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
                   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
                   )
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL )
#define FOLLOW_LEXS to_set32( ENDFILE )

// internal sets

Block * Block::compile( Environment * e ) {

        lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_BLOCK );

        while (lex_isinset( START_PUNCS, START_KEYS, START_LEXS )) {


