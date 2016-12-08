//<record> ::= "record" [ "+" <reference> ] <block> "end"


#ifndef EXTERN 
#define EXTERN extern
#endif

class record {
public:
   static record * compile( Environment * e );



private:

// nothing lives here yet

};

#undef EXTERN
