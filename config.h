/* config.h -- configuration constants for compiler */

/* Author: Douglas W. Jones
 * Date 9/9/2016 -- added errors raised by string pool
 */

#ifndef CONFIG_H
#define CONFIG_H

#define POOL_SIZE 100
/* the size of the string pool where all the text of identifiers and strings
 * is stored.  This constant is used in strings.h and strings.c
 */

#define SYMBOL_SIZE 100

#define SYMBOL_HASH 7

#endif