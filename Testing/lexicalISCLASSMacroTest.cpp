#include <iostream>
#include "../lexical.h"

/*
 * by Alex Dan and hongxu.
 * we want to excersize the ISCLASS macro from lexical.cpp
 *
 */

int main(int argc, char** argv){
  const unsigned int numChars = 256;
  const unsigned int numCharTypes = 5;


  static const char * const charTypes []= { "Other",
                            "Whitespace",
                            "Letter",
                            "Bullshit",
                            "Digit",
                            "mor", "dum","crap",
                            "Punctuation", "error1", "error2"  };

  try {
    for( int i = 0; i < numChars; ++i) {
      printf("$%d:Char was: %c",i, static_cast<char>(i));
      //printf("\tType was: %d\n", getCharType( static_cast<char>(i) ));
      printf("\tType was: %s\n", charTypes[getCharType(i)]);
    }


  }
  catch(std::exception &excp) {
  std::cout << "got an exception!! It was :" << excp.what() <<std::endl;
  return -1;
  }
  return 0;
}

