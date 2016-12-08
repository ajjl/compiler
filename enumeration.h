//<enumeration> ::= "enum" "(" <identifier> { [ "," ] <identifier>} ")"
//               |  "enum" "[" <identifier> { [ "," ] <identifier>} "]"
//               |  "enum" "{" <identifier> { [ "," ] <identifier>} "}"


#ifndef EXTERN 
#define EXTERN extern
#endif

class enumeration {
public:
   static enumeration * compile( Environment * e );



private:

// nothing lives here yet

};

#undef EXTERN
