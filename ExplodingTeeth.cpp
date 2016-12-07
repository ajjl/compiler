#include <iostream>

#define STACKBOTTOM 4
#define STACKTOP 13


#if 0
#ifndef EXTERN
	#define EXTERN extern
#endif

EXTERN unsigned int sp = STACKBOTTOM;
#undef EXTERN
#endif

class AssemblyProclamationOfTheWorkersParadise {
private:
	static unsigned int sp = STACKBOTTOM;

public:

    // File * output; //Right now we'll just use std::out

    static void incStack(){
        sp++;
        if(sp >= STACKTOP){
            std::cerr << "stack overflow!!!!!" << std::endl;
            exit(-2);
        }
    }

    static void dncStack(){
        sp--;
        if(sp <= STACKBOTTOM){
            std::cerr << "stack underflow!!!!!" << std::endl;
            exit(-2);
        }
    }

    static void PUSHL(/*int x*/){ // Only use 1 word (4byte) size vars
	incStack();
    };
    static void POPL(int x){
	dncStack();
    };
    static void PUSHI( int c){
	// change to stack later
	std::cout << "add r" << sp << " #0 " << c << std::endl;
	incStack();
    };

#if 0 
    static void PUSHGA( int a ) {

    };
    static void LOAD(){

    };
    static void POPS(){

    };
    static void POPSH (){}:
    static void POPSB (){}:
    static void DUP (){}:
    static void ADD (){}:
    static void SUB (){};
    static void MUL (){};
    static void DIV (){};
    static void MOD (){};
    static void GT (){};
    static void LT (){};
    static void GE (){};
    static void LE(){};
    static void EQ(){};
    static void BTRUE (int dst){};
    static void BFALSE (int dst){};
    static void BR (int dst){};
    static void LABEL (int dst){};
    static void PUSHLA (int d){};

#endif
};
