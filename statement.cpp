#include "errors.h"
#include "stringpool.h"
#include "symboltable.h"
#include "keywords.h"
#include "lexical.h"
#include "lexsupport.h"
#include "block.h"

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

    #if Debugging_statement
	//lex_this.print_lex();
    #endif
    if(lex_this.type != IDENT){ // not an identifier so it is an if statement
        if(lex_this.value == KEY_IF){ // we got an if

            lex_advance(); // eat the if
            lexeme firstCompartor = lex_this;
            lex_advance(); //advance the window
            lexeme comparisonOperator = lex_this;
            lex_advance(); //advance the window
            lexeme secondComparator = lex_this;
            lex_advance();


            //comparisonOperators currently supported -> "="
            if(comparisonOperator.value == PT_EQUALS ||  comparisonOperator.value == PT_NOTEQL){ //we got an equals !!

                //first comparator must be reference ( a variable??)
                //load and compare it
                //get offset of var
                int offset = e->lookup(firstCompartor.value);
                load_value_into_working_register(offset);
                compare_working_register_with_constant(secondComparator.value);
                int label = make_conditional_jump_label((comparisonOperator.value) );
                //compile statement(assignment)
                Block::compile(e);
                // print the closing jump label
                print_closing_jump_label(label);

                //std::cout << "lex after if?? " << std::endl;
                //lex_this.print_lex();

                return NULL; //done with comparison


            }

        }

    }
    lexeme first = lex_this; // should be our identifier if this is an assignement

    lex_advance();



    // see if the lexeme is an equals
    if (lex_this.type == 4 && lex_this.value == 2) {
        // it's an assignment statement
        lex_advance();

        int offsetAssignee = e->lookup(first.value);
        //(e)->addElement(first.value);
        //lex_this.print_lex();
        if(lex_next.value == PT_SEMI && lex_this.type == NUMBER) { // then assign a constant
            declare_and_assign(offsetAssignee, lex_this.value);
        }
        else if(lex_this.type == IDENT && lex_next.value == PT_PLUS){ // assign result of adding to var; ie. x = y + 1;
            int offsetOtherAssign = e->lookup(lex_this.value); //look up y

            load_value_into_working_register(offsetOtherAssign);
            lex_advance(); //eat the second ident
            lex_advance(); //eat the plus sign
            int value = lex_this.value; //the value of the number constant
            add_constant_to_working_register(value);
            store_working_register_into_memory(offsetAssignee);





        }
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
