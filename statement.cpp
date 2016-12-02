#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"

#include "environment.h"

#define EXTERN
#include "statement.h"
/*statement.cpp is the file copied from jones, maybe borrow the idea from professor and delete the file*/
// =BUG= code to compile <if> <case> <for loop> <while loop> <do loop>
// =   =                 <exception handler> <raise> <procedure call>
// =   =                 <assignment>
// =   = could all go here as local classes, not in the header file
// =   = but if they start getting big and unwieldy, they can each
// =   = be put in ther own files

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

	std::cout << "In statement compile." << std::endl;
	std::cout << "First wantinset" << std::endl;
        lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_STATE );
        // =BUG= big kluge!! statement stub just eats one lexeme

	lex_this.print_lex();
        lex_advance();
	std::cout << "This should be a fucking '='" << std::endl;
	
	lex_this.print_lex();

	std::cout << "Follow wantinset" << std::endl;
        lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_BLOCK );

        // =BUG= do statements need to return any attributes?
        return NULL;
}
