//<type declarator> ::= "type" <type>
//                   |  "type" "-"

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

#include "typeDeclarator.h"

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



Environment * typeDeclarator::compile( Environment * e ){
   std::cout<< "in typeDeclarator::compile"<< std::endl;
   std::cout<<"Environment is: " << e << std:endl;
   char message[300];
   std::sprintf(message, "value of lexeme in, %s: %d", _FILE_, _LINE_);
   lex_this.print_lex(message);
   lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_BLOCK );
   while ( lex_isinset( START_PUNCS, START_KEYS, START_LEXS )){
 std::cout<<"in while loop of typeDeclarator::Compiler"<<std::endl;
 // the above code might change, trying to build a model now 
 
   lex_this.print_lex();
   
   if ( (lex_this == "type") && lex_next == TYPE/*keyword TYPE*/){
    std::cout<<"I think I am a type declarator with keyword type"<<std::endl;
    e = typeDeclaration::compile(e);
}   

   else if ( (lex_this == "type")&& lex_next == "-"/*a minus symol*/){
    std::cout<<"I think I am a type declarator with minus symbol"<<std::endl;
    e = typeDeclaration::compile(e);
}   

   else{
   std::cout<<"I am not a type expression, I do not know what I am doing here"<<std::endl;
   }
  if(lex_ispunc( lex_this, PT_SEMI)){
   std::cout<<"this is the end of current typeDeclarator::compile"<<std::endl; 
    lex_advance();

}   
}   
std::cout<<"after whileloop of typeDeclarator::compile"<<std::endl;
return NULL;
}
 

