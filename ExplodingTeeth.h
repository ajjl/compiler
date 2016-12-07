
#include <iostream>

#define STACKBOTTOM 4
#define STACKTOP 13

#ifndef EXTERN
#define EXTERN extern
#endif

    extern int sp;


    // File * output; //Right now we'll just use std::out

    void incStack();

    void dncStack();

    void PUSHL(/*int x*/); // Only use 1 word (4byte) size vars
    void POPL(int x);
    void PUSHI( int c);

#undef EXTERN
