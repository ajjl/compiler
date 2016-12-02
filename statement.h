#ifndef EXTERN
#define EXTERN extern
#define Debugging_statement 1
#define FOLLOW_PUNCS to_set32( PT_SEMI )
#define FOLLOW_KEYS ( START_KEYS                                           \
                    | to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL ) \
                    )
#define FOLLOW_LEXS to_set32_2( ENDFILE, IDENT )


#endif

/* this file is the header file of statement.cpp, the exist or not exist 
 * together, credit from jones file
 */

class Statement {
public:
        static Statement * compile( Environment ** e );
        // factory method

        // =BUG= do statements have any attributes?  they are missing here
};

#undef EXTERN
