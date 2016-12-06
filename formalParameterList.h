//formalParameterList.h

//bnf <formal parameter list> ::= "(" <formal parameters> ")"
 //                        |  "[" <formal parameters> "]"
//                         |  "{" <formal parameters> "}"



#ifndef EXTERN 
#define EXTERN extern
#endif

class formalParameterList {
public:
        static formalParameterList * compile( Environment * e );

private:

};

#undef EXTERN



