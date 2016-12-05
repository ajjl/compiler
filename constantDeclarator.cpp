/*<constant declarator> ::= "const" <expression>
                       |  "final" <expression>

<expression> ::= <comparand> [ <comparing operator> <comparand> ]

*/

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
#include <iostream>
#include <cstdio>
#include "statement.h"

#include "constantDeclarator.h"

//start set
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
                   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
                   )
//follow set

#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL )
#define FOLLOW_LEXS to_set32( ENDFILE )

#include <iostream>

//internal sets

Environment * ConstantDeclarator::compile( Environment * e ){
   std::cout<< "in ConstantDeclarator::compile"<< std::endl;
   std::cout<<"Environment is: " << e << std:endl;
   char message[300];
   std::sprintf(message, "value of lexeme in, %s: %d", _FILE_, _LINE_);
   lex_this.print_lex(message);
   lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_BLOCK );
   while ( lex_isinset( START_PUNCS, START_KEYS, START_LEXS )){
 std::cout<<"in while loop of ConstantDeclarator::Compiler"<<std::endl;
 // the above code might change, trying to build a model now 

   lex_this.print_lex();

   if ( (lex_this == "const") && lex_next == EXP/*EXPRESSION*/){
    std::cout<<"I think I am a constant declarator with const"<<std::endl;
    e = ConstantDeclaration::compile(e);
}

   else if ( (lex_this == "final")&& lex_next == EXP/*EXPRESSION*/){
    std::cout<<"I think I am a constant declarator with final"<<std::endl;
    e = ConstantDeclaration::compile(e);
}

   else{
   std::cout<<"I am not a constant expression, I do not know what I am doing here"<<std::endl;
   }
  if(lex_ispunc( lex_this, PT_SEMI)){
   std::cout<<"this is the end of current constantDeclarator::compile"<<std::endl;
    lex_advance();
}
}
std::cout<<"after whileloop of constantDeclarator::compile"<<std::endl;
return NULL;
}
  
