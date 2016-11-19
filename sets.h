/* sets.h -- a fast lightweight implementation of set operations */

/* Author: Douglas W. Jones
 * Date 8/19/2016 -- pasted from Lecture 12 with pro-forma improved comments
 */

/* This set implementation uses 32-bit integers as bit vectors to hold sets
 * as such, the domain must contain 32 or fewer elements
 *
 * the basic set operations are:
r*    a & b - the intersection of sets a and b
 *    a | b - the union of sets a and b
 *    ~ a   - the inverse of set a (that is a tilde, not a - sign)
 *
 * This implementation is entirely in the header file, there is no .c file
 */
#ifndef SETS_H
#define SETS_H

#include <stdint.h>

typedef uint32_t set32_t;
/* the type of sets over domains containing up to 32 elements */
#ifndef SET32_EMPTY
#define SET32_EMPTY ((set32_t)0)
#endif

/* set32_t to_set32( int i ) */
#ifndef to_set32
#define to_set32(i)   (((set32_t)1)<<(i))
#endif
/* construct a single-member set32_t value from one integer or enumeration */

/* set32_t to_set32_2( int i, int j ) */
#ifndef to_set32_2
#define to_set32_2(i,j)     (to_set32(i) | to_set32(j))
#endif
/* construct set32_t value from 2 integers */

/* set32_t to_set32_3( int i, int j, int k ) */
#ifndef to_set32_3
#define to_set32_3(i,j,k)   (to_set32(i) | to_set32(j) | to_set32(k))
#endif
/* construct set32_t value from 3 integers */

/* set32_t to_set32_4( int i, int j, int k, int l ) */
#ifndef to_set32_4
#define to_set32_4(i,j,k,l) (to_set32_2(i,j) | to_set32_2(k,l))
#endif


/* test set membership */

/* bool in_set32( int i, set32_t s ) */
#ifndef in_set32
#define in_set32(i,s) (to_set32(i) & s)
#endif

/* test if integer in set32_t, returns nonzero if so, zero if not */

#endif
