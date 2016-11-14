
/*THE MANTAINANCE LAYER: MEMPRY MANAGEMENT FUNCTION*/


#include <stdio.h>
#include<stdlib.h>
#include<tools/debug.h>
#include<tools/hash.h>
#include<tools/1.h>
#include<tools/compiler.h>
#include<tools/c-code.h>
#include "symtab.h"
/*SYMBOL TABLE DEFINITIONS*/  
#include"value.h"
/*VALUE DEFINITIONS*/
#include"proto.h"
/*PROTOTYPES FOR ALL FUNCTIONS IN THIS DIRECTORY*/
#include"lable.h"
/*LABLES TO USE FOR COMPILER GENERATED SYMBOLS*/


PRIVATE symbol  *Symbol_free = NULL;
/*Free_list of recycled symbols. */
PRIVATE link  *Link_free = NULL;
/*FREE LIST OF RECYCLED LINKS*/
PRIVATE structdef *Struct_free = NULL;
/*Free LIST RECYCLED STRUCTDEFS*/

#define LCHUNK  10
/*new_link() gets this many nodes at one shot.*/

PUBLIC symbol *new_symbol( name, scope )

char *name;
int scope;
{
   symbol *sym_p;
   if (!Symbol_free)   /*FREE LIST IS EMPTY*/
       sym_p = (symbol *)  newsym( sizeof(symbol) );
   else{       /*UNLINK NODE FROM THE FREE LIST*/
      sym_p = Symbol_free;
      Symbol_free = Symbol_free->next ;
      memset( sym_p, 0, sizeof(symbol) );
}
strncpy( sym_p->name, name, sizeof(sym_p->name) );
sym_p->level = scope;
return sym_p;
}



PUBLIC void discard_symbol( sym )
symbol *sym;
{
/*DISCARD A SINGLE SYMBOL STRUCTURE AND ANY ATTACHED LINKS AND ARGS, BOTE THAT THE ARGS FIELD IS RECYCLED FOR INITIALIZERS.*/

if( sym )
{
  if( IS_FUNC( sym->type ) )
     discard_symbol_chain( sym->args );
/*FUNCTION ARGUMENTS BEFORE*/
  else /*IF ANY INITIALIZES.*/
    discard_value( (value *)sym->args );
   discard_link_chain( sym->type );
/*Discard type chain*/
   sym->next = Symbol_free;
/*PUT CURRENT SYMBOL*/
   Symbol_free = sym;
 /*IN THE CURRENT LIST*/
}
}

/*---------------------------------------------------------------------*/



PUBLIC void discard_symbol_chain(sym)
/*DISCARD AN ENTIRE CRESS LINKED CHAIN OF SYMBOLS*/
symbol *sym;
{
  symbol *p = sym;
  while( sym )
{
p = sym->next;
discard_symbol(sym);
sym = p;
}
}


/*-----------------------------------------------------------------*/

PUBLIC link *new_link()
{
/*RETURN A NEW LINK, IT IS INITIALIZED TO ZEROS, SO IT IS A DECLARATOR BY DEFINITION. LCHUNK NODES ARE ALLOCATED FROM MALLOC() AT ONE TIME.*/


  link *p;
  int i;

  if ( !Link_free )
{
  if( !(Link_free = (link *) malloc( sizeof (link) * LCHUNK )))
  {
     yyerror("INTERNAL, new_link; Out of memory\n");
     exit( 1 );
}
  for( p = Link_free, i = LCHUNK; --i>0; ++p )
/*EXECUTE LCHUNK-1 TIMES*/
    p->next = NULL;
}

p = Link_free;
Link_free = Link_free->next;
memset( p, 0, sizeof(link));
return p;
}

/*--------------------------------------------------------------*/

PUNLIC void discard_link_chain(p)
link *p;
{
link *start ;

if ( start = p )
{ 
  while ( p->next ) 
  /*find last node*/
  p = p->next;
  p->next = Link_free;
  Link_free = start;
}
}



/*-------------------------------------------------------------*/

PUBLIC void discard_link( p )
/*discard a single link*/
link *p;
{
  p->next = Link_free;
  Link_free = p;
}

/*------------------------------------------------------------*/

PUBLIC structdef *new_structdef ( tag )
/* ALLOCATE A NEW STRUCTDEF */
char *tag;
{
  struct *sdef_p;
  if( !Struct_free )
     sdef_p = (structdef *)  newsym( sizeof(structdef) );
else
{
sdef_p = Struct_free;
Struct_free = (structdef *) (Struct_free->fields);
memset( sdef_p, 0, sizeof(sdef_p->tag) );
return sdef_p;
}

/*------------------------------------------------------------*/

PUNLIC void discard_structdef( sdef_p )
structdef *sdef_p;
{
/*DISCARD A STRUCTDEF AND ANY ATTACHED FIELDS, BUT DO NOT DISCARD LINKED STRUCTURE DEFINITIONS*/
if ( sdef_p )
{
  discard_symbol_chain( sdef_p -> fields );
  sdef_p->fields = (symbol *) Struct_free ; 
  Struct_free = sdef_p:
}
}


/*-------------------------------------------------------------*/


/*MEMORY MANAGEMENT FUNCTION1 OVER*/

/*next part starts here*/



/*THE MAINTENANCE LAYER, DECLARATOR MANIPULATION*/

PUBLIC void add_declarator( sym, type )
symbol *sym;
int type;
{
link *link_p;
if( type == FUNCTION && IS_ARRAY(sym-> etype) )
{
yyerror("Array of function is illegal, assuming function pointer\n");
add_declarator( sym, POINTER );
}

link_p   = new_link();
/*THE DEFAULT CLASS IS DECLARATOR*/
link_p->DCL_TYPE = type;

if ( !sym->type)
   sym->type = sym->etypr = link_p;
else
{
  sym->etype->next = link_p;
  sym->etype = link_p;
}
}

/*DECLARATOR MANIPULATION CODE FINISH LINE*/


/*THE MAINTENANCE LAYER: SOECIFIER MANIPULATION*/
PUBLIC spec_cpy( dst, src )
/*COPY ALL INITIALIZED FFIELDS IN SRC TO DSC. */
link *dst, *src;
{
  if( src->NOUN  ) dst->NOUN =src->NOUN ;
  if( src->SCLASS  ) dst->SCLASS =src->SCLASS ;
  if( src->LONG  ) dst->LONG =src->LONG ;
  if( src->UNSIGNED  ) dst->UNSIGNED =src->UNSIGNED ;
  if( src->STATIC  ) dst->STATIC =src->STATIC ;
  if( src->EXTERN  ) dst->EXTERN =src->EXTERN ;
  if( src->tdef  ) dst->tdef =src->tdef ;

  if(src->SCLASS == CONSTANT || src->NOUN == STRUCTURE)
     MEMCPY( &DST->value, &SRC->VALUE, sizeof(src->VALUE) );
}



/*THE END OF SPECIFIER MANIPULATION CODE*/
/*-----------------------------------------------------------------*/




/*THE MAINTENANCE LAYER: TYPE MANIPULATION*/

PUBLIC link *clone_type( tchain, endp )
link *tchain;
/*input; TYPE CHAIN TO DUPLICATE.*/
link **endp;
/*output: POINTER TO LAST NODE IN CLONED CHAIN. */
{
 /*mANUFACTURE A CLONE OF THE TYPE CHAIN IN THE INPUT SYMBOL.  RETURN A POINTER TO THE CLONED CHAIN, NUL IF THERE WERE NO DECLARATORS TO CLONE. TDEF BIT IN THE COPY IS ALWAYS CLEARED.*/

link *last, *head = NULL;
for(; tchain; tchain = tchain->next )
{
if( !head )
/*first node in chain*/
  head = last= new_link();
else  /*Subsequent node*/
{
 last->next = new_link();
last = last->next;
}
memcpy( last, tchain, sizeof (*last));
last->next = NULL;
last->tdef = 0;
}
*endp = last;
return head;
}


PUBLIC int the_same_type( p1, p2, relax )
link *p1, *p2;
int relax;
{
/*return 1 if the types match, 0 if they do not, ignore the storage class, if "relax" is true and the array declarator is the first link in the chain, then a pointer is considered equivalent to an array.*/

if ( relax && IS_PTR_TYPE(pl) && IS_PTR_TYPE(p2))
{
  p1 = p1-> next;
  p2 = p2->next;
}
for(; p1 && p2 ; p1 =p1->next, p2=p2->next)
{
  if ( p1->class != p2->class)
    return 0;
  if( p1->class == DECLARATOR )
{
  if ( (p1->DCL_TYPE != P2->dcl_type) ||
         (p1->DCL_TYPE==ARRAY && (p1->NUM_ELE != p1->NUM_ELE)))
    return 0;
}
else /*THIS IS DONE LAST*/
{
if( (p1->NOUN == p2->NOUN )  && (p1->LONG == p2->LONG ) && (p1->UNSIGNED==p2->UNSIGNED))
{
return ( p1->NOUN ==STRUCTURE) ? p1->V_STRUCT == p2->V_STRUCT:1;
}
return 0;
}
}
yyerror("INTERNAL the_same_type: unknown link class\n");
return 0;
}

/*----------------------------------------------------------------------*/




PUBLIC int get_sizeof(p)
link *p;
{
/*RETURN THE SIZE OF BYTES OF AN OBJECT OF THE TYPE POINTED TO BY P.  functions are considered to be a pointer sized because that is how they are represented internally*/

int size;

if ( p->class == DECLARATOR )
   size = (p->DCL_TYPE == ARRAY) ? p->NUM_ELE *get_sizeof(p->next) : PSIZE;

else
{
 switch( p->NOUN )
{
case CHAR: size = CSIZE; break;
case INT: size = p->LONG ? LSIZE : ISIZE; break;
case STRUCTURE: size = p->V_STRUCT->size; break;
case VOID: size = 0;  break;
case LABLE: size = 0; break;
}
}
return size;
}

/*---------------------------------------------------------------------*/


PUBLIC symbol *reverse_links ( sym )
symbol *sym;
{
/*GO THROUGH THE CROSS LINKED CHAIN OF SYMBOLS, REVERSING THE DIRECTION OF THE CROSS POINTERS, RETURN A POINTER TO THE NEW HEAD OF CHAIN WHICH IS FORMERLY THE END OF THE CHAIN OR NULL IF THE CHAIN STARTED OUT EMPTY.*/

symbol *previous, *current, *next;

if( !sym )
   return NULL;

previous = sym;
current = sym->next;

while ( current )
{
next  = current->next;
current->next = previous;
previous = current;
current = next;
}

sym->next = NULL;
return previous;
}


/*END OF TYPE MANIPULATION*/


/*THE MAINTENANCE LAYER: SYMBOL PRINTING FUNCTIONS*/

PUBLIC char *sclass_str( class )
/* RETURN A STRING REPRESENTING THE INDICATED STORAGE CLASS.*/
int class;
{
 return class == CONSTANT ?"CON":
        class == REGISTER ?"REG":
        class == TYPEDEF  ?"TYP":
        class == AUTO     ?"AUT":
        class == FIXED    ?"FIX": "BAD SCLASS";
}

/*--------------------------------------------------------------------*/

PUBLIC char *oclass_str( class )
/*RETURN A STRING REPRESENTING THE INDICATED OUTPUT STORAGE CLASS*/
int class;
{
  return class == PUB ? "PUB" :
         class == PRI ? "PRI" :
         class == COM ? "COM" :
         class == EXT ? "EXT" : "(NO OCLS)";
}
/*----------------------------------------------------------------------*/


PUBLIC char *noun_str(noun)
/* Return a string representing the indicated noun.*/
int noun;
{
  return noun==INT  ?"int" :
         noun==CHAR ?"CHAR" :
         noun==VOID ?"void" :
         noun==LABLE ?"lable" :
         noun == STRUCTURE ?"struct" : "BAD NOUN";
}
/*-------------------------------------------------------------------------*/

PUBLIC char *attr_str(spec_p )
/*RETURN A STRING REPRESENTING ALL*/
specifier *spec_p;
/*attributes in a specifier other than the noun and storage class.*/
{
 static char str[5]:
 str[0] = ( spec_p->_unsigned ) ? 'u' : '.' ;
 str[1] = ( spec_p->_static ) ? 's' : '.' ;
 str[2] = ( spec_p->_extern ) ? 'e' : '.' ;
 str[3] = ( spec_p->_long ) ? '1' : '.' ;
 str[4] = '\0';
}

/*---------------------------------------------------------------------------*/

PUBLIC char *type_str ( link_p )
link *link_p;
/*return a string representing the type represented by the link chain*/
{
 int i;
 static char target [80];
 static char buf [64 ];
 int available = sizeof(target) =1;

 *buf = '\0';
 *target = '\0';

 if ( !link_p )
  return "(NULL)";
 if(link_p-> tdef )
{
 strcpy( target, "tdef " );
 available -= 5;
}

for(; link_p: link_p = link_p->next )
{ 
  if ( IS_DECLARATOR(link_p) )
  {
   switch( link_p->DCL_TYPE )
{
case POINTER: i = sprintf(buf, "*"); break;
case ARRAY:  i = sprintf(buf, "[%d]", link_p->NUM_ELE); break;
case FUNCTION: i = sprintf(buf, "()"); break;
default: i = sprintf(buf, "BAD DECL"); break;
}
}
else /* it is a specifier */
{
 i = sprintf( buf, "%s %s %s %s", noun_str ( link_p->NOUN ),
                                  sclass_str ( link_p->SCLASS ),
                                  oclass_str ( link_p->OCLASS ),
                                  attr_str (&link_p->select.s ));
 if ( link_p->NOUN == STRUCTURE || link_p->SCLASS == CONSTANT )
{
   strncat( target, buf, available );
   available -= i ;
   
  if ( link_p->NOUN != STRUCTURE )
   continue;
  else
{
    i = sprintf(buf, " %s", link_p->V_STRUCT->tag ?
                            link_p->V_STRUCT->tag : "untagged");
}
}

 strncat( target, bufm available );
 available -= i ;
}
return target;}

/*----------------------------------------------------------*/

PUBLIC char *tconst_str (type )
link *type;
/* RETURN A STRING REPRESENTING THE VALUE FIELD AT THE END OF THE SPECIFIED TYPE WHICH MUST BE CHAR POINTER , CHAR, INT, LONG, UNSIGNED INT, OR UNSIGNED LONG. RETURN "?" IF THE TYPE IS NOT ANY OF THESE. */

{
 static char buf[80];
 buf[0] = '?';
 buf[1] = '\0';
 
if (IS_POINTER(type) && IS_CHAR(type->next))
{
 sprintf( buf, "%s%d", L_STRING, type->next->V_INT );
}
else if( !(IS_AGGREGATE(type) || IS_FUNCT(type)))
{
  switch( type->NOUN )
  {
  case CHAR:


