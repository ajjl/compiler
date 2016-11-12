


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



