
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



`
