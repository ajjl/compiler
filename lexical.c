/* lexical.c -- lexical analyzer implementation */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 */

#include <stdio.h>
#include <stdint.h>

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
    PT_NOT    /* ~ */,   PT_DOT    /* . */
} punct_type;

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

/******
 * global variables for the lexical analyzer
 ******/

static FILE * infile; /* the input file */
static char ch;       /* the most recent character */

/******
 * implementation
 ******/

/* =BUG= lex_open needs writing, initializes infile, ch, lex_this, lex_next */

void lex_advance() {

	/* slide the lexical analysis window forward */
	lex_this = lex_next;
	
	while (ISCLASS(ch,WHITESPACE)) {
		/* skip whitespace */
		ch = getc( infile );
		/* =BUG= what if this hits the end of file? */
		/* =BUG= how do we handle comments? */
	}
	if (ISCLASS(ch,DIGIT)) {
		/* decimal digit */
		lex_next.type = NUMBER;
		lex_next.value = 0;
		do {
			if ( lex_next.value > ((UINT32_MAX - (ch - '0'))/10) ) {
				/* =BUG= report number out of bounds */
			} else {
				/* accumulate value of digit */
				lex_next.value = (lex_next.value*10)+(ch - '0');
			}

			/* get the next digit */
			ch = getc( infile );
			/* =BUG= what if this hits the end of file? */
		} while (ISCLASS(ch,DIGIT));
	} else if (ISCLASS(ch,PUNCTUATION)) {
		lex_next.type = PUNCT;
		lex_next.value = punct_class[ch];
		ch = getc( infile );
		/* =BUG= what if this hits the end of file? */
		/* =BUG= what about 2-character punctuation marks? */
	} else {
		/* =BUG= what about identifiers, strings, punctuation */
	}
}
