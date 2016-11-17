/* incomplete code*/

unsigned hash_pjw( unsigned char  *name )
{
   unsigned hash_val =0;
   unsigned i;

   for(; *name ; ++name )
   {
     hash_val = (hash_val << 2) + *name;
     if( i = hash_val & 0x3fff )
         hash_val = (hash_val ^ (i >> 12)) & ~0x3fff ;
   }
   return hash_val;
}
/* I will try to fix you, later */

/*16 bit hashpjw implementation code*/



