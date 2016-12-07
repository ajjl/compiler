#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"
#include "ExplodingTeeth.h"

#define EXTERN
#include "statement.h"
/*statement.cpp is the file copied from jones, maybe borrow the idea from professor and delete the file*/
// =BUG= code to compile <if> <case> <for loop> <while loop> <do loop>
// =   =                 <exception handler> <raise> <procedure call>
// =   =                 <assignment>
// =   = could all go here as local classes, not in the header file
// =   = but if they start getting big and unwieldy, they can each
// =   = be put in ther own files

#define Debugging_statement 0

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
                   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
                   )
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
                    | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL ) \
                    )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )

Statement * Statement::compile( Environment * e ) {

    #if Debugging_statement
	std::cout << "In statement compile." << std::endl;
	std::cout << "First wantinset" << std::endl;
    e->print();
    e->printAll();
    #endif

    lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_STATE );
    // =BUG= big kluge!! statement stub just eats one lexeme

    #if Debugging_statement
	//lex_this.print_lex();
    #endif
    lexeme first = lex_this; // should be our identifier

    lex_advance();


    // see if the lexeme is an equals
    if (lex_this.type == 4 && lex_this.value == 2) {
        // it's an assignment statement
        lex_advance();
        //(e)->addElement(first.value);
        int offset = e->lookup(first.value);
        declare_and_assign(offset, lex_this.value);


        #if Debugging_statement
        (e)->printAll();
        #endif
    } else {
#if Debugging_statement
        std::cout << "gimme an equals sign" << std::endl;
#endif
    }

    lex_advance();

#if Debugging_statement
    std::cout << "Follow wantinset" << std::endl;
#endif
    lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_BLOCK );

    // =BUG= do statements need to return any attributes?
    return NULL;
}
