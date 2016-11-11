#define BYTE_WIDTH        1     /* WIDETH OF THE BASIC TYPES*/
#define WORD_WIDTH        2
#define LWORD_WIDTH       4
#define PTR_WIDTH         4

#define BYTE_HIGH_BIT  "0XFF80"   /*HIGH-BIT MASK. */
#define WORD_HIGH_BIT  "0X8000"

#define LWORD_HIGH_BIT "0X80000000L"



#define SWIDTH  LWORD_WIDTH  /* STACK WIDTH (IN BYTES).  */

#define SDEPTH   1024     /* Number of elements in stack. */

#define ALIGN_WORST  LWORD_WIDTH  /* lONG WORD IS WORST CASE ALIGNMENT. */

