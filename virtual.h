//This is a base version of code generation file, continued work is required for matching previous files

#include <tools/c-code.h>
/*BASIC TYPES*/
typedef char byte; /*8 BIT*/
typedef short word; /*16 bit*/
typedef long 1word; /*32 bit*/
typedef char *ptr; /*Nominally 32 bit*/

typedef byte array;/* Aliases for "byte"*/
typedef byte record;

#ifdef ALLOC
#  define I(x)  x
#  define CLASS /*EMPTY*/
#endif

struct _words{ word low,high;};
struct _bytes{ byte b0, b1, b2, b3; };  /* b0 is LSB, b3 is MSB*/

typedef union reg
{
   char    *pp   /* pointer     */
   1word   1;    /*long word    */
   struct _words  w;   /* two 16-bit words*/
   struct _bytes b;    /* four 8-bit bytes*/
   
}
reg;


CLASS reg r0, r1, r2, r3, r4, r5, r6, r7;  /* REGISTERS*/
CLASS reg r8, r9, rA, rB, rC, rD, rE, rF; /*end*/

CLASS reg stack [ SDEPYTH ] ; /*run-time stack*/
CLASS reg *__sp I (= &stack [SDEPTH]);  /* Stack pointer*/
Class reg  *__fp I (= &stack [SDEPTH]); /* frame pointer*/


#define fp   ((char *) __fp)

#define sp   ((char *) __sp) 

#define SEG(segment)   /* empty */

#define public   /* empty*/
#define common   /* empty*/
#define private  static
#define external extern
/* storage classes*/

# define ALIGN (type)  /*empty*/

#define W   *(word *)
#define B   *(byte *)
#define L   *(1word *)
#define P   *(ptr  *)
#define WP  *(word **)
#define BP  *(byte **)
#define LP  *(1word **)
#define PP  *(ptr   **)
/* direct stack access directives*/
#define push(n)  (--sp) -> 1 = (1word) (n)
#define pop(t)  (t)( (sp++)->1 )
/*pushing and popping*/
#define PROC(name, cls) cls name(){
#define ENDP(name)  ret();}/*NAME IS IGNORED*/

#define call(name) (--__sp) ->pp = #name, (*(void  (*)()) (name))()

#define ret ()   __sp++; return

/*subroutine definition, calls and returns*/
#define link(n)  ((--__sp)->pp = (char *)__fp), (__fp = __sp), (__sp -= (n))

#define unlink() (__sp = (reg *)__fp), (__fp = (reg *)((__sp++)->pp))
/*subroutine linkage directices*/

#define 1rs(x,n)  (((x) = ((unsigned long)(x) >> (n)))
/*the logical right shift directives*/


#define ext_low(reg)  (reg.w.low = (word )reg.b.b0 )
#define ext_high(reg) (reg.w.high = (word ).reg.b.b2)
#define ext_word(reg) (reg.1  = (1word)reg.w.low )
/*Sign-Extension Directives*/
#define EQ(a,b)  if ( (long) (a) == (long)(b) )
#define NE(a,b)  if ( (long) (a) != (long)(b) )
#define LT(a,b)  if ( (long) < (long)(b) )

