//procedureDeclarator header file

//BNF notation <procedure declarator> ::= "procedure"
 //                                     [ <formal parameter list> ]
 //                                     <body>


#ifndef EXTERN 
#define EXTERN extern
#endif

class procedureDeclarator {
public:
        static procedureDeclarator * compile( Environment * e );


private:

};

#undef EXTERN



