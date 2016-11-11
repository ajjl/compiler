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
