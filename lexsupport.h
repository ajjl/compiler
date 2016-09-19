/* lexsupport.h -- lexical analyzer support interface specificaton */

/* Author: Douglas W. Jones
 * Date 8/19/2016 -- pasted from Lecture 12 with pro-forma improved comments
 * 
 * Note, before including this file, the user must include:
 *    <stdint.h>
 *    "lexical.h"
 *    "sets.h"
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

/* bool lex_ispunc( lexeme lex, punct_type t ); */
#define lex_ispunc(lex,t) (					\
	(lex.type == LEX_PUNC) && (lex.value == t)		\
)
/* returns true if lexeme lex is a punctuation mark of type t */

/* bool lex_ispuncset( lexeme lex, set32_t s ); */
#define lex_ispuncset(lex,s) (					\
	(lex.type == LEX_PUNC) && in_set32(lex.value, s)	\
)
/* returns true if lexeme lex is a punctuation mark in set t */

bool lex_forcepunc( punct_type t );
/* force lex_this to be the punctuation mark t and advance over it */

#undef EXTERN
