/*continued work is required for matching previous files  */

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
#define LT(a,b)  if ( (long) (a) <  (long)(b) )
#define LE(a,b)  if ( (long) (a) <= (long)(b) )
#define GT(a,b)  if ( (long) (a) >  (long)(b) )
#define GE(a,b)  if ( (long) (a) >= (long)(b) )
/*LONG*/

#define U_LT(a,b) if( (unsigned long) (a) < (unsigned long) (b) )
#define U_GT(a,b) if( (unsigned long) (a) > (unsigned long) (b) )
#define U_LE(a,b) if( (unsigned long) (a) <=(unsigned long) (b) )
#define U_GE(a,b) if( (unsigned long) (a) >=(unsigned long) (b) )
/*UNSIGNED LONG*/

#define BIT(b,a)  if( (s) & (1 << (b)) )

/*COMPARISON DIRECTIVES*/

#define _main   main

#ifdef ALLOC
pm()
{
   reg *p;
   int i;
   
  /*PRINT THE VIRTUAL MACHINE( REGISTERS AND TOP 16 STACK ELEMENTS). */
  
  printf("r0= %081x  r1= %081x r2=%081x r3=%081x\n",  
          r0.1,       r1.1,      r2.1,     r3.1,      );
  printf("r4= %081x  r5= %081x r6=%081x r7=%081x\n",  
          r4.1,       r5.1,      r6.1,     r7.1,      );
  printf("r8= %081x  r9= %081x rA=%081x rB=%081x\n",  
          r8.1,       r9.1,      rA.1,     rB.1,      );
  printf("rC= %081x  rD= %081x rE=%081x rF=%081x\n",  
          rC.1,       rD.1,      rE.1,     rF.1,      );

  if( __sp >= &stack[SDEPTH] )
       printf("Stack is empty\n");
  else 
       printf("\nitem byte real addr   b3 b2 b1 b0    hi  lo     1\n");

  for( p = __sp, i=16; p< &stack[SDEPTH]  &&  --i>=0  ++p  )
  {
     printf("%04d %04d %9p  [%02x|%02x|%02x|%02x] = [%04x|%04x] = [%081x]",
       p-__sp,      (p-__sp)*4,    (void far *)p,
       p->b.b3 & 0xff,    p->b.b2 & 0xff,  p->b.b1 & 0xff,  p->b.b0 & 0xff,
       p->w.high & 0xffff,  p->w.lowp->w.low & 0xffff,
       p->1
     );

     if( p == __sp )  printf("<-SP");
     if( p == __fp )  printf("<-FP");
     printf("\n")
  }
}

#endif

/*RUN TIME TRACE SUPPORT*/

