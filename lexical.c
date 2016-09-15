/* lexical.c -- lexical analyzer implementation */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/9/2016  -- code for identifiers and strings from Lecture 8
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "errors.h"
#include "stringpool.h"
#include "config.h"
#include "symboltable.h"

#define EXTERN
#include "lexical.h"

/******
 * the character classifier
 ******/

typedef enum {
	OTHER=0, WHITESPACE=1, LETTER=2, DIGIT=4, PUNCTUATION=8
} char_type;

/* short forms of character types used in the classifier table */
#define OTH OTHER
#define WIT WHITESPACE
#define LET LETTER
#define DIG DIGIT
#define PUN PUNCTUATION

/* character classifier table */
static const char_type char_class[256] = {
     /* NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI  */
	OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,WIT,WIT,WIT,WIT,WIT,OTH,OTH,
     /* DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US  */
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     /*      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /  */
        WIT,OTH,OTH,OTH,OTH,PUN,PUN,OTH,PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
     /*  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?  */
	DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,PUN,PUN,PUN,PUN,PUN,OTH,
     /*  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  */
        PUN,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
     /*  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _  */
        LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,OTH,PUN,OTH,OTH,
     /*  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o  */
        OTH,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
     /*  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL */
        LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,PUN,PUN,PUN,OTH,
     /* beyond ascii */
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
};

/* get rid of short definitions */
#undef OTH
#undef WIT
#undef LET
#undef DIG
#undef PUN

#define ISCLASS(ch,class) (char_class[ch]&(class))

/******
 * the punctuation classifier
 ******/

/* table mapping from characters to punctuation names */
static const punct_type punct_class[256] = {
     /* NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /* DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /*      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /  */
        PTX,PTX,PTX,PTX,PTX,PT_MOD,
			        PT_AND,
        			    PTX,PT_LPAREN,
        				    PT_RPAREN,
        					PT_TIMES,
        					    PT_PLUS,
							PT_COMMA,
							    PT_MINUS,
								PT_DOT,
								    PT_DIV,
     /*  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PT_COLON,
						    PT_SEMI,
							PT_LT,
							    PT_EQUALS,
								PT_GT,
								    PTX,
     /*  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /*  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PT_LBRAKT,
        						PTX,PT_RBRAKT,
								PTX,PTX,
     /*  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /*  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PT_LBRACE,
        						PT_OR,
							    PT_RBRACE,
								PT_NOT,
								    PTX,
     /* beyond ascii */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
};

/* table mapping from punctuation names to text strings for lex_put */
/* WARNING:  strings must be given in the order enumerated in punct_type */
static const char * punct_name[] = {
    /* PTX */ "?WHAT?", /* this should never happen */
    /* "PT_SEMI   */ ";", /* PT_EQUALS */ "=", /* PT_COLON  */ ":",
    /* "PT_LPAREN */ "(", /* PT_LBRAKT */ "[", /* PT_LBRACE */ "{",
    /* "PT_RPAREN */ ")", /* PT_RBRAKT */ "]", /* PT_RBRACE */ "}",
    /* "PT_COMMA  */ ",", /* PT_ATSIGN */ "@", /* PT_ELIPS  */ "..",
    /* "PT_NOTEQL */ "/=", /*PT_GT     */ ">", /* PT_GE     */ ">=",
    /* "PT_LT     */ "<", /* PT_LE     */ "<=", /*PT_PLUS   */ "+",
    /* "PT_MINUS  */ "-", /* PT_TIMES  */ "*", /* PT_DIV    */ "/",
    /* "PT_MOD    */ "%", /* PT_AND    */ "&", /* PT_OR     */ "|",
    /* "PT_NOT    */ "~", /* PT_DOT    */ "."
};

/******
 * global variables for the lexical analyzer
 ******/

static FILE * infile;  /* the input file */
static int ch;         /* the most recent character */
static int line_number;/* the line number in infile */

/******
 * implementation
 ******/

void lex_open( char * f ) {
	/* open file f for input, or use stdin if f is null */
	if (f != NULL) {
		infile = fopen( f, "r" );
		if (infile == NULL) error_fatal( ER_BADFILE, 0 );
	} else {
		infile = stdin;
	}

	/* initialize the sliding window */
	ch = fgetc( infile );
	line_number = 1;
	lex_advance();
	lex_advance();
}

void lex_advance() {

	/* slide the lexical analysis window forward */
	lex_this = lex_next;

	while ((ch != EOF) && ISCLASS(ch,WHITESPACE)) {
		/* skip whitespace */
		ch = getc( infile );
		if (ch == '\n') line_number = line_number + 1;
	}
	if (ch == EOF) {
		lex_next.type = ENDFILE;
		lex_next.value = 0; /* irrelevant */
	} else if (ISCLASS(ch,LETTER)) {
		/* identifier or possibly a keyword */
		lex_next.type = IDENT;
		symbol_start( line_number ); /* =BUG= ? */
		do {
			/* save the character */
			symbol_append( ch ); /* =BUG= ? */
			/* get the next character */
			ch = getc( infile );
		} while ((ch != EOF) && ISCLASS(ch,LETTER|DIGIT));
		lex_next.value = symbol_lookup();
		/* =BUG= must call either string_accept() or _reject() */
		/* =BUG= lex_next.value must be must be set to something */
	} else if (ISCLASS(ch,DIGIT)) {
		/* decimal digit */
		lex_next.type = NUMBER;
		lex_next.value = 0;
		do {
			if ( lex_next.value > ((UINT32_MAX - (ch - '0'))/10) ) {
				error_warn( ER_TOOBIG, line_number );
			} else {
				/* accumulate value of digit */
				lex_next.value = (lex_next.value*10)+(ch - '0');
			}

			/* get the next digit */
			ch = getc( infile );
		} while ((ch != EOF) && ISCLASS(ch,DIGIT));
		/* =BUG= what if a # leads into an odd number base? */
	} else if ((ch == '"') || (ch == '\'')) {
		/* string */
	       	unsigned char quote = ch; /* remember what quote mark to use */
		lex_next.type = STRING;
		symbol_start( line_number ); /* =BUG= ? */
		ch = getc( infile );
		while ((ch != EOF) && (ch != '\n') && (ch != quote)) {
			symbol_append( ch ); /* =BUG= ? */
			/* get the next letter of the string */
			ch = getc( infile );
		}
		lex_next.value = symbol_lookup();
		/* =BUG= must call either string_accept() or _reject() */
		/* =BUG= lex_next.value must be must be set to something */
		if (ch == quote) {
			/* get the next character after the closing quote */
			ch = getc( infile );
		} else {
			error_warn( ER_BADSTR, line_number );
		}
	} else if (ISCLASS(ch,PUNCTUATION)) {
		lex_next.type = PUNCT;
		lex_next.value = punct_class[ch];
		ch = getc( infile );
		if ((lex_next.value == PT_MINUS) && (punct_class[ch] == PT_MINUS)) { // begin comment
			while ((ch != EOF) && (ch != '\n')) {
				ch = getc( infile );
			}
		}
		if ((lex_next.value == PT_GT || lex_next.value == PT_LT || lex_next.value == PT_DIV) && (punct_class[ch] == PT_EQUALS)) {
			if (lex_next.value == PT_GT) {	/* greater than or equal */
				lex_next.value = PT_GE;
				ch = getc( infile );
			} else if (lex_next.value == PT_LT) {	/* less than or equal */
				lex_next.value = PT_LE;
				ch = getc( infile );
			} else if (lex_next.value == PT_DIV) {	/* not equal */
				lex_next.value = PT_NOTEQL;
				ch = getc( infile );
			}
		}
	} else {
		/* =BUG= what about identifiers, strings */
	}
}

void lex_put( lexeme * lex, FILE * f ) {
	/* reconstruct the text of the lexeme */
	switch (lex->type) {
	case IDENT:
	case KEYWORD:
		symbol_put( lex->value, f );
		/* =BUG= how to print an identifier or keyword? */
		break;
	case NUMBER:
		fprintf( f, "%" PRId32, lex->value );
		break;
	case PUNCT:
		fputs( punct_name[lex->value], f );
		break;
	case STRING:
	case ENDFILE:
		fputs( "EOF", f );
			/* =BUG= missing code for these lexeme types */
		break;
	}
}
