//<parameter declarer> ::= <type>
//                      |  "var" <type>
//                      |  "final" <type>

#ifndef EXTERN 
#define EXTERN extern
#endif

class parameterDeclarer {
public:
   static parameterDeclarer * compile( Environment * e );



private:

// nothing lives here yet

};

#undef EXTERN
