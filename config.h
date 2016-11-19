/* config.h -- configuration constants for compiler */

/* Author: Douglas W. Jones
 * Date 9/9/2016 -- added errors raised by string pool
 */

/* should not define the same thing twice based on the effeciency of the program*/


#ifndef CONFIG_H
#define CONFIG_H

#define DASH '-'
/* the filename path delimeter on this system, - for Unix, / for Windows */

#define DEFAULT_NAME "Kestrel"
/* the default name for this program if no name is given on the command line */

#define POOL_SIZE 3000
/* the size of the string pool where all the text of identifiers and strings
 * is stored.  This constant is used in strings.h and strings.c
 */

#define SYMBOL_SIZE 1000

#define SYMBOL_HASH 7

#endif
