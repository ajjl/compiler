#include <iostream>
#include "../lexsupport.h"

int main()
{
  bool value = false;
  lexeme myLexeme;
  myLexeme.type = PUNCT;
  myLexeme.value = 3;

  value = lex_ispunc(myLexeme, 3);
  if(value) 
  {
    std::cout << "test passed!!" << std::endl;
  }
  else
  {
    std::cout << "test failed :(" << std::endl;
  }
  return !value ;
}
