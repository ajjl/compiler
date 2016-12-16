#include "program.h"
#define EXTERN
#include "ExplodingTeeth.h"

 int sp = STACKBOTTOM;
 int jumpLabel = 2;
    // File * output; //Right now we'll just use std::out

   void incStack(){
        sp++;
        if(sp >= STACKTOP){
            std::cerr << "stack overflow!!!!!" << std::endl;
            exit(-2);
        }
    }

   void dncStack(){
        sp--;
        if(sp <= STACKBOTTOM){
            std::cerr << "stack underflow!!!!!" << std::endl;
            exit(-2);
        }
    }

    void PUSHL(/*int x*/){ // Only use 1 word (4byte) size vars
        incStack();
    }

    void POPL(int x){
        dncStack();
    }

    void PUSHI( int c){
        // change to stack later
        std::cout << "add r" << sp << " #0 " << c << std::endl;
        incStack();
    }

    void POPS(){

		//temp = M[sp++];
		//M[M[sp++]] = temp;
    }

    // alternate method

    void declare_and_assign(int offset, int value) {
    	// caller must do environment lookup to get offset
    	// r7 must be initialized as a something (frame?) pointer
        if(silent == 1) {
            std::cout << "mov r3, #" << value << std::endl;
            std::cout << "str r3, [r7, #" << offset << "]" << std::endl;
        }
    }

    void load_value_into_working_register(int offset) {
        if(silent == 1) {
            std::cout << "ldr r3, [r7, #" << offset << "]" << std::endl;
        }

    }

    void compare_working_register_with_constant(int constant) {
        if(silent == 1) {
            std::cout << "cmp r3, #" << constant << std::endl;
        }
    }

    int make_conditional_jump_label(){
        if(silent == 1) {
            std::cout << "bne .L" << jumpLabel << std::endl;
        }
       return jumpLabel++; //return the jump label, then increment for the next jump
    }
    void print_closing_jump_label(int label){

        if(silent == 1) {
            std::cout << ".L" << label << ":" << std::endl;
        }

    }

    void generate_prolog(int bigOffset) {
        if(silent == 1) {
            std::cout << ".global main" << std::endl;
            std::cout << "main:" << std::endl;
            std::cout << "push {r7}" << std::endl;
            std::cout << "sub sp, sp, #" << bigOffset << std::endl;
            std::cout << "add r7, sp, #0" << std::endl;
        }

    }

    void generate_epilog(int bigOffset) {
        if(silent == 1) {
            std::cout << "mov r0, r3" << std::endl; //return last used var
            std::cout << "add r7, r7, #" << bigOffset << std::endl;
            std::cout << "mov sp, r7" << std::endl;
            std::cout << "pop {r7}" << std::endl;
            std::cout << "bx lr" << std::endl;
        }
  
    }


/*
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
*/
// SUPRISE !!!
