
#ifndef EXTERN
	#define EXTERN extern
#endif

/* this file is the header file of statement.cpp, the exist or not exist 
 * together, credit from jones file
 */

class Statement {
public:
        static Statement * compile( Environment * e );
        // factory method

        // =BUG= do statements have any attributes?  they are missing here
};

#undef EXTERN
