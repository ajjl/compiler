// formalParameters.h

//bnf <formal parameters> ::= <parameter> { [ "," ] <parameter> }


#ifndef EXTERN 
#define EXTERN extern
#endif

class formalParameters {
public:
        static formalParameters * compile( Environment * e );

private:

};

#undef EXTERN



