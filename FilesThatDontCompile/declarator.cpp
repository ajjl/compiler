<declaration> ::= <identifier> ":" [ "private" | "restricted" ] <declarator>
<declarator> ::= <constant declarator>
              |  <type declarator>
              |  <exception declarator>
              |  <variable declarator>
              |  <procedure declarator>
              |  <function declarator>


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "sets.h"
#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"

#define EXTERN
#include "declarator.h"
// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS SET32_EMPTY
#define START_LEXS to_set32( IDENT )
// follow sets
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
                    | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL ) \
                    )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )

Environment * Declarator::compile( Environment * e ) {
   std::cout<<"in Declarator::compile"<<std::endl;
   lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_??? );
  // need to put declarator into the environment 
   std::cout<<"PRINTING ELEMENTS"<<std::endl;
   e->addElement(lex_this.value, 0);
   //if this is <constant declarator>


   // if this is <type declarator>

   // if this is <exception declarator>

   // if this is <variable declarator>
  
   // if this is <procedure declarator>
  
   // if this is <function declarator>


   // all the above accepted as <declarator> 



   // to be continued
   lex_this.print_lex();
   lex_advance();
   std::cout << "end of Declarator::Compile" << std::endl;

   return e;// maybe not e?

}

   
  
