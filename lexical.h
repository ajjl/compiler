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
#include "keywords.h" //=BUG= keywords needs to be declared before the ifdef extern thing??


#ifndef EXTERN
	#define EXTERN extern
#endif
#include <iostream>

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
    PT_NOT    /* ~ */,   PT_DOT    /* . */,   PT_DD     /* .. */
} punct_type;

class lexeme {
public:
	lex_types type; /* type of this lexeme */
	uint32_t value; /* value of this lexeme, meaning depends on type */
	int line;	/* line number from which this lexeme came */
	std::string debugVal;

	void print_lex(){
		std::cout << "lex_type is: " << this->type << std::endl;
		std::cout << "lex_value is: " << key_lookup(static_cast<string_handle >(this->value))<< std::endl;
		std::cout << "lex_line is: " << this->line<< std::endl;
	}
	void print_lex(std::string message){
		print_lex();
		std::cout << message << std::endl;
	}
} ;

EXTERN lexeme lex_this; /* the current lexeme */
EXTERN lexeme lex_next; /* the next lexeme */

void lex_open( const char * f );
void lex_advance();
void lex_put( lexeme * lex, FILE * f );

#undef EXTERN
#endif
