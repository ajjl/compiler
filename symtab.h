


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

 
