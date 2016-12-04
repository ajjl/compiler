/*Code generation file, cpp file*/

/* WE NEED TO SLOWLY LOWER THE ABSTRACTION LEVEL SLOWLY, LIKE ONE STEP A TIME TO WRITE THIS PART, IT IS ALSO GOOD FOR DEBUG*/

/* AFTER CHECK THE SEMANTICS, THIS PART WILL BE USED*/

/*POSSIBLY THERE WILL BE SOME OPTIMIZATIONS BETWEEN SOME PASSES TO MAKE THE ENTIRE PROCESS BETTER*/


/* WE ALSO NEED TO ADD TETING METHOD FOR CODE GENERATION SO WE CAN TREAT BUG WISELY AND EFFECIENTLY*/

/* GUIDELINE OF CODE GENERATOR CPP ENDS HERE*/

/*THIS CODE DOES NOT COMPILE NOW*/

#if 0


/* first of all, need to divide different symbols and keywords into different sub parts*/

/* AS AN ARRAY */
/* tHE TABLE NAME IS GOING TO BE CHANGED*/

newTable[]={
{ "=", mathSymbol },
{ "+". mathSymbol },
{ "-", mathSymbol },
/* * means multiple and pointer in c++, but in Kestrel? */
{ "*", mathSymbol },
{ "/", mathSymbol },
{ "%", mathSymbol },
{ "//", mathSymbol},
/* HOW TO DIVIDE '//' AND '/' , SURELY '//' SHOULD BE IN HIGHER PRIORITY*/
{"!", logicalSymbol},
{"==", logicalSymbol},
{"<", comparisonSymbol},
{">", comparisonSymbol},
{"<=", comparisonSymbol},
{"=<", comparisonSymbol},
{">=", comparisonSymbol},
{"=<", comparisonSymbol},
/* FOR EXAMPLE, case, statemnet maybe should be adding here*/



/* SURELY WE NEED TO DISTINGUISH SYMBOLS STUCK TOGETHER GENERAL SITUATION AND SPECIAL OCCASIONS*/

/* there are still many things to fill in this table */



}
 

/* NEED TO ADD FUNCTION SWITCH BETWEEN CASES*/

/* need to check structures of finding certain key words,
add pointer on for example "while" w->h->i->l->e->recon"while" key word,
just a reminder.*/

/* should be differ from states, like state1 --w-->state2 etc*/

#endif
#ifndef EXTERN
#define EXTERN extern
#endif
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

#define DEFAULT_SIZE 1000

class Stack {
   char *arr;
   int tos, capacity;
 public:
   Stack();
   Stack(int size);

   ~Stack();
   void push(char a);
   char pop();
   int get_size();
   bool is_empty();
   bool is_full();
   void display();
   char get_top();


};

Stack::Stack() {
arr = new char[DEFAULT_SIZE];
tos = 0;
capacity = DEFAULT_SIZE;
}

Stack::Stack(int size) {
 arr = new char[size];
 tos = 0;
 capacity = size;
}

Stack::~Stack() {
  delete[] arr;
}

void Stack::push(char a){
  if (!is_full()){
     arr[tos++] = a;
     cout<<"pushing"<<endl;
}
  else
    cout << "Sorry, the stack is full, push failed."<< endl;
}

char Stack::pop(){
   if( !is_empty()){
     return arr[--tos];
}

else{
  cout<< "Sorry, the stack is empty, pop failed."<<endl;
  return -1;
}
}

char Stack::get_top() {
  if (!is_empty())
      return arr[tos-1];
  else{
    cout<< "sorry, the stack is empty, pop failed."<<endl;
}
}

int Stack::get_size(){
 return tos;

}

bool Stack::is_empty() {
  if(tos == 0)
      return true;
  else
       return false;

}

bool Stack:: is_full(){
  if ( tos == capacity)
      return true;
  else
      return false;

}


void Stack:: display() {
 if ( tos == 0 )
   cout<< "The stack is empty"<< endl;
 else{
    for ( int i=0; i<tos; i++)
        cout << arr[i]<<" ";
        cout<<endl;
}
}

/* when using
stack_push
stack_pop
default size 1000;
*/

