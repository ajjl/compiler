//Constantdeclarator.h file


#ifndef EXTERN 
#define EXTERN extern
#endif


//BNF

//<constant declarator> ::= "const" <expression>
//                       |  "final" <expression>

class ConstantDeclarator{
public:
   static ConstantDeclarator * compile( Environment * e);
// constant declarator has attributes in public section
//they are missing here   

private:

//nothing lives here yet


};

#undef EXTERN


