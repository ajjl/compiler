/* lexical.h -- lexical analyzer interface specificaton */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- pasted from Lecture 4 with pro-forma improved comments
 *
 */
#ifndef LEXICAL_H
#define LEXICAL_H

#include <stdio.h>
#include <stdint.h>

#include "errors.h"
#include "stringpool.h"
#include "config.h"
#include "symboltable.h"


#ifndef EXTERN
	#define EXTERN extern
#endif

typedef enum {
         OTHER=0, WHITESPACE=1, LETTER=2, DIGIT=4, PUNCTUATION=8
} char_type;

int getCharType(char myChar);
//char_type getCharType(char myChar);

typedef enum { IDENT, KEYWORD, NUMBER, STRING, PUNCT, ENDFILE } lex_types;

/* names for specific punctuation marks */
typedef enum {
    PTX       /* not a punctuation mark */,
    PT_SEMI   /* ; */,   PT_EQUALS /* = */,   PT_COLON  /* : */,
    PT_LPAREN /* ( */,   PT_LBRAKT /* [ */,   PT_LBRACE /* { */,
    PT_RPAREN /* ) */,   PT_RBRAKT /* ] */,   PT_RBRACE /* } */,
    PT_COMMA  /* , */,   PT_ATSIGN /* @ */,   PT_ELIPS  /* .. */,
    PT_NOTEQL /* /= */,  PT_GT     /* > */,   PT_GE     /* >= */,
    PT_LT     /* < */,   PT_LE     /* <= */,  PT_PLUS   /* + */,
    PT_MINUS  /* - */,   PT_TIMES  /* * */,   PT_DIV    /* / */,
    PT_MOD    /* % */,   PT_AND    /* & */,   PT_OR     /* | */,
    PT_NOT    /* ~ */,   PT_DOT    /* . */,   PT_CMNT   /* -- */
} punct_type;

typedef struct lexeme {
	lex_types type;
	uint32_t value;
} lexeme;

EXTERN lexeme lex_this; /* the current lexeme */
EXTERN lexeme lex_next; /* the next lexeme */

void lex_open( const char * f );
void lex_advance();
void lex_put( lexeme * lex, FILE * f );

#undef EXTERN
#endif
