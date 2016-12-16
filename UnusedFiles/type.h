//EBNF <type> ::= <reference>
//        |  <enumeration>
//        |  <subrange>
//        |  <pointer>
//        |  <array>
//        |  <set>
//        |  <record>


#ifndef EXTERN 
#define EXTERN extern
#endif

class type {
public:
   static type * compile( Environment * e );



private:

// nothing lives here yet

};

#undef EXTERN
