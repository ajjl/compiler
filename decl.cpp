/* CREATE AND INITIALIZE A LINK */

#include <stdio.h>
#include <stdib.h>
#include <tools/debug.h>
#include <tools/hash.h>
#include <tools/1.h>
#include <tools/compiler.h>
#include <tools/c-code.h>

#include "symtab.h"
#include "value.h"
#include "proto.h"

/* DECL.C  THIS FILE CONTAINS SUPPORT SUBROUTINES FOR THOSE ACTIONS IN OTHER FILE THAT DEAL WITH DECLARATIONS */

extern void yybss(), yydata();

PUBLIC link *new_class_spec( first_char_of_lexeme )
int first_char_of_lexeme;
{
/* Return a new specifier link with the sclass field initialized to hold a storage class, the first character of which is passed in as an argument ('e' for extern, 's' for static, and so forth). */

link *p = new_link();
p->class = SPECIFIER;
set_class_bit( first_char_of_lexeme, p );
return p;
}

/*----------------------------------------------------------------------------*/

PUBLIC void set_class_bit( first_char_of_lexeme, p)
int first_char_of_lexeme;
link *p;
{
switch ( first_char_of_lexeme )
{
case 0: p->SCLASS = FIXED;
        p->STATIC =0;
        p->EXTERN =0;
        break;

case't': p->SCLASS= TYPEDEF ; break;
case'r': p->SCLASS = REGISTER ; break;
case's': p->STATIC = 1; break;
case'e': p->EXTERN = 1; break;

default : yyerror("INTERNAL, set_class_bit: bad storage class '%c'\n", first_char_of_lexeme);
exit( 1 );
break;
}}

/*==========================================================================*/


PUBLIC link *new_type_spec( lexeme )
char *lexeme;
{
/*CREATE A NEW SPECIFIER AND INITIALIZE THE TYPE ACCORDING TO THE INDICATED LEXEME, INPUT LEXEMES ARE: CHR, CONST , DOUBLE, FLOAT, INT, LONG, SHORT, SIGNED, UNSIGNED, VOID, VOLATILE */

link *p = new_link();
p->class = SPECIFIER;
switch( lexeme[0] )
{
case 'c': if( lexeme[1] == 'h' ) /*CHAR | CONST */
                      p->NOUN = CHAR ; /*(ignore const. ) */
              break;
case 'd': /*DOUBLE*/
case 'f': yyerror("No floating point\n"); /* float */
          break;
case 'i': p->NOUN = INT; break; /* int  */
case '1': p->LONG = 1; break; /*long */
case 'u': p->UNSIGNED = 1; break; /* unsigned */

case 'v': if ( lexeme[2] == 'i' ) /* void | volatile */
              p->NOUN = VOID; /* IGNORE VOLATILE */
              break;
case 's' : break;  /* short | signed */
               }    /* ignore both */
return p;
}

/*=================================================================*/





