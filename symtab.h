/*<TOOLS/DEBUG.H> AND <TOOLS/HASH.H> MUST BE #INCLUDED IN THE SAME ORDER SHOWN BEFRE, BERFORE #INCLUDE THIS CURRENT FILE*/


#ifdef ALLOC
#   define ALLOC_CLS /* empty */
#else
#   define ALLOC_CLS   extern
#endif

/*ALLOCATE VARIABLE IF ALLOC defined. */


/*to be continued*/

#define NAME_MAX  32
/*MAX IDENTIFIER LENGTH*/
#define LABLE_MAX  32
/*MAX OUTPUT LABLE LENGTH*/

typedef struct symbol
/*symbol-table entry.  */
{
   unsigned char   name [NAME_MAX+1];
   /*INPUT VARIABLE NAME*/
   unsigned char rname [NAME_MAX+1];
   /*ACTUAL VARIABLE NAME*/
   
   unsigned level  :13;
   /*DECLARATION LEVEL, FIELD OFFSET*/
   unsigned implicit  : 1 ; 
   /*DECLARATION CREATED IMPLICITLY*/
   unsigned duplicate  : 1 ;
   /*DUPLICATE DECLARATION. */

   struct  link  *type;
   /*First link in declarator chain*/
   struct  link  *etype;
   /*Last link in declarator chain*/
   struct symbol  *args;
   /*IF A FUNCTION DECL, THE ARG LIST. */
   /*IF A VAR, THE INITIALIZER.  */
   struct  symbol *next;  
   /*current nesting level*/
 } symbol;

 ALLOC_CLS HASH_TAB  *Symbol_tab;
 /*The actual table.  */

#define POINTER   0
#define ARRAY     1
#define FUNCTION  2
/*VALUES FOR DECLARATOR.TYPE*/

typedef struct declarator
{
  int dcl_type;
  /* POINTER, ARRAY, OR FUNCTION  */
  int num_ele;
  /* If class==ARRAY, NUMBER OF ELEMENTS  */
} declarator;


#define INT 0
#define CHAR 1
#define VOID 2
#define STRUCTURE 3
#define LABLE 4
/* specifier.noun. INT has the value 0 so that an uninitialized structure defaults to int, same goes for EXTERN BELOW.  */




/*SPECIFIER.SCLASS  */
#define FIXED 0 
/*at a foxed address*/
#define REGISTER 1
/*IN A REGISTER */
#define AUTO 2
/*ON THE RUN-TIME STACK*/
#define TYPEDEF 3
/*TYPEDEF*/
#define CONSTANT 4
/*tHIS IS A CONSTANT*/



/*OUTPUT C-CODE STORAGE CLASS*/
#define NO_OCLASS 0
/*no, output class(var is auto).  */
#define PUB  1
/*PUBLIC*/
#define PRI 2
/*PRIVATE*/
#define EXT 3
/* extern */
#define COM 4
/*common*/


typedef struct specifier
{
  unsigned noun :3;
/* CHAR INT STRUCTURE LABLE */
  unsigned sclass :3;
/*REGISTER AUTO FIXED CONSTANT TYPEDEF*/
  unsigned oclass :3;
/*OUTPUT STORAGE CLASSES, PUB PRI COM EXT*/
  unsigned _long :1;
/*1= long; 0 = short*/
  unsigned _unsigned :1;
/*1=unsigned , 0-signed;*/
  unsigned _static :1;
/*1=static keyword found in declarations. */
  unsigned _extern :1;
/*1=extern keyword found in declarations. */

union
{
/*value if constant*/
int v_int;
/* INT &CHAR VALUES. IF A STRING CONST IS NUMERIC COMPONENT OF THE LABLE*/
unsigned int v_unit; 
/*UNSIGNED INT CONSTANT VALUES*/
long v_long;
/*signed long constant value.*/
unsigned long v_ulong; 
/* UNSIGNED LONG CONSTANT VALUE*/
struct structdef *v_struct;
/*IF THIS IS A STRUCT, POINTS AT A STRUCTURE TABLE ELEMENT.*/
} const_val;
} specifier;


/*SPECIFIER COMPLETE*/


/*A LINK IN THE DECLARATION CHAIN*/
#define DECLARATOR  0
#define SPECIFIER   1

typedef struct link
{
  unsigned class : 1;
/*DECLARATOR OR SPECIFIER*/
  unsigned tdef :1;
/*FOR TYPEDEFS, IF SET, CURRENT LINK CHAIN WAS CREATED BY A TYPEDEF*/
  union
  {
  specifier  s;
/*IF CLASS == DECLARATOR*/
  declarator d;
/*IF CLASS == SPECIFIER*/
}
select;
struct link *next;
/*next element of the chaiin*/
} link;
/*use p->XXX where p is a pointer to a link structure*/
#define NOUN   selct.s.noun
#define SCLASS  select.s.sclass
#define LONG   select.s._long
#define UNSIGNED  select..s._unsigned
#define EXTERN   select.s._extern
#define STATIC   select.s._static
#define OCLASS   select.s.oclass


#define DCL_TYPE   select.d.dcl_type
#define NUM_ELE    select.d.num_ele


#define VALUE   select..s.const_val
#define V_INT   VALUE.v_int
#define V_UNIT  VALUE.v_unit
#define V_LONG  VALUE.v_long
#define V_ULONG VALUE.v_ulong
#define V_STRUCT  VALUE.v_struct

/*USE XXX(p) where p us a pointer to a link structure.*/

#define IS_SPECIFIER(p)  ( (p)->class == SPECIFIER )
#define IS_DECLARATOR(p)  ( (p)->class == DECLARATOR)
#define IS_ARRAY(p)  ( (p)->class == DECLARATOR && (p)->DCL_TYPE==ARRAY  )
#define IS_POINTER(p)  ( (p)->class == DECLARATOR && (p)->DCL_TYPE==POINTER )
#define IS_FUNCT(p)  ( (p)->class == DECLARATOR && (p)->DCL_TYPE==FUNCTION)
#define IS_STRUCT(p)  ( (p)->class == SPECIFIER && (p)->NOUN == STRUCTURE )
#define IS_LABLE(p)  ( (p)->class ==SPECIFIER && (p)->NOUN == LABLE  )



#define IS_CHAR(p)   ( (p)->class == SPECIFIER && (p)->NOUN == CHAR )
#define IS_INT(p)   ( (p)->class ==SPECIFIER && (p)->NOUN == INT  )
#define IS_UNIT(p)  ( IS_INT(p) && (p)->UNSIGNED  )
#define IS_LONG(p)  ( IS_INT(p) && (p)->LONG  )
#define IS_ULONG(p)  ( IS_INT(p) && (p)->LONG && (p)->UNSIGNED  )
#define IS_UNSIGNED(p)  ( (p)->UNSIGNED  )


#define IS_AGGREGATE(p)  ( IS_ARRAY(p) || IS_STRUCT(p)   )
#define IS_PTR_TYPE(p)  (IS_ARRAY(p) || IS_POINTER(p) )


#define IS_CONSTANT(p)  (IS_SPECIFIER(p) && (p)->SCLASS == CONSTANT  )
#define IS_TYPEDEF(p)  (IS_SPECIFIER(p) && (p)->SCLASS == TYPEDEF  )
#define IS_INT_CONSTANT(p)  (IS_CONSTANT(p) && (p)->NOUN == INT  )


/*DECLARATION LINK CHAIN 1 FINISHED LINE*/








