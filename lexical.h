/* lexical.h -- lexical analyzer interface specificaton */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- pasted from Lecture 4 with pro-forma improved comments
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

enum lex_types { IDENT, KEYWORD, NUMBER, STRING, PUNCT, ENDFILE };

typedef struct lexeme {
	lex_types type;
	uint32_t value;
} lexeme;

EXTERN lexeme lex_this; /* the current lexeme */
EXTERN lexeme lex_next; /* the next lexeme */

void lex_open( char * f );
void lex_advance();
void lex_put( lexeme * lex, FILE f );

#undef EXTERN
