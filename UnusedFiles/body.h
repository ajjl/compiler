// body header file

// <body> ::= <block> "end"
//           |  "-"
//           |  "external"


#ifndef EXTERN 
#define EXTERN extern
#endif

class Body {
public:
        static Body * compile( Environment * e );

private:

};

#undef EXTERN



