
#include <iostream>
//#include "lexical.h"

#define STACKBOTTOM 4
#define STACKTOP 13

#ifndef EXTERN
#define EXTERN extern
#endif

    extern int sp;

    extern int jumpLabel;


    // File * output; //Right now we'll just use std::out

    void incStack();

    void dncStack();

    void PUSHL(/*int x*/); // Only use 1 word (4byte) size vars
    void POPL(int x);
    void PUSHI( int c);
    void declare_and_assign(int offset, int value);
    void load_value_into_working_register(int offset);
    void compare_working_register_with_constant(int constant);
    int make_conditional_jump_label(int comparisonType);
    void print_closing_jump_label(int label);

    void generate_prolog(int bigOffset);
    void generate_epilog(int bigOffset);

#undef EXTERN
