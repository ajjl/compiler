/* lexical.c -- lexical analyzer implementation */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 */

#include <stdio.h>

#define EXTERN
#include <lexical.h>

/* the character classifier */
enum char_type ( OTHER=0, WHITESPACE=1, LETTER=2, DIGIT=4, PUNCTUATION=8 );

/* short forms of character types */
#define OTH OTHER
#define WIT WHITESPACE
#define LET LETTER
#define DIG DIGIT
#define PUN PUNCTUATION

/* character classifier table */
static const chart_type char_class[256] = {
     /* NUL SOH STX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI  */
	OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,WIT,WIT,WIT,WIT,WIT,OTH,OTH,
     /* DLE ....
        OTH,  ....
     /*      !   "
}

#define ISCLASS(ch,class) (char_class[ch]&(class))

static FILE * infile; /* the input file */
static char ch;       /* the most recent character */

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
			/* accumulate value of digit */
			lex_next.value = (lex_next.value * 10)+(ch - '0');
			/* =BUG= what if there's an overflow? */

			/* get the next digit */
			ch = getc( infile );
			/* =BUG= what if this hits the end of file? */
		} while ((ch >= '0')&&(ch <= '9'));
	} else {
		/* =BUG= what about identifiers, strings, punctuation */
	}
}
	}
}
