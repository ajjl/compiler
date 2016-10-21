// main.cpp -- main program for a Kestrel compiler */

// Author: Douglas W. Jones
// Date 9/30/2016 -- code from lecture 17 with pro-forma comment changes

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sets.h"
#include "config.h"
#include "errors.h"
#include "lexical.h"
#include "program.h"

#define EXTERN
#include "main.h"

int main( int argc, char * argv[] ) {

	bool isinfile = false;  // has the input file been specified?
	bool isoutfile = false; // has the output file been specified?
	int i; // indexing the argument number in argv

	// first, deal with the program name
	main_progname = DEFAULT_NAME; // from config.h

	if ((argc > 0)              // Unix/Linux shells guarantee this
	&&  (argv[0] != NULL)       // Unix/Linux implies this
	&&  (argv[0][0] != '\0')) { // but nonstarndard exec could do this
		main_progname = argv[0];
	}
	// assert: program name is now well defined

	// set argument strings to indicate that they have not been set
	main_infile = NULL;  // this means read from stdin
	main_outfile = NULL; //            write to stdout

	// then deal with the command line arguments
	i = 1; // start with the argument after the program name
	while ((i < argc) && (argv[i] != NULL)) { // for each arg
		const char * arg = argv[i]; // this argument
		char ch = *arg;     // first char of this argument

		if ( ch == '\0' ) {
			// ignore empty argument strings

		} else if ( ch != DASH ) {
			// arg not starting with dash is the input file name
			if (isinfile) { // too many input files given
				error_fatal( ER_EXTRAINFILE, 0 );
			}
			main_infile = arg;
			isinfile = true;

		} else {
			// command line -option
			arg++; // strip skip over the leading dash
			ch = *arg; // first char of argument

			if (ch == '\0') { // - by itself
				// ... meaning read stdin
				if (isinfile) { // input files already given
					error_fatal( ER_EXTRAINFILE, 0 );
				}
				isinfile = true;

			} else if (ch == 'o') {
				// -o outfile or -o=outfile or -ooutfile
				if (isoutfile) { // too many files
					error_fatal( ER_EXTRAOUTFILE, 0 );
				}
				arg++; // strip off the letter o
				ch = *arg;
				if (ch == '\0') { // -o filename
					i = i + 1;
					if ((i > argc) && (argv[i] != NULL)) {
						error_fatal( ER_MISSINGFILE,0 );
					}

					// =BUG= what about -o -

					main_outfile = argv[i];
					isoutfile = true;
				} else { // -ofilename or -o=filename
					if (ch == '=') {
						arg++; // strip off the =
						ch = *arg;
					}
                			if (ch == '\0') {
						error_fatal( ER_MISSINGFILE,0 );
					}

					// =BUG= what about -o- and -o=-

					main_outfile = arg;
					isoutfile = true;
        			}

			// put code to parse other options here

			} else if (!strcmp( arg, "help" )) { // -help
				er_help();

			} else if (!strcmp( arg, "?" )) { // -? means help
				er_help();

			} else {
				error_fatal( ER_BADARG, 0 );

			}
		}      
		i++; // advance to the next argument
	}

	/* now, we have the textual file names */

	if ((!isoutfile) && (main_infile != NULL)) { /* compute main_outfile */

		int j = 0;
		int dot = -1;
		while (main_infile[j] != '\0') {
			if (main_infile[j] == '.') dot = j;
			j++;
		}
		if (dot == -1) dot = j;
		// dot is index of last dot in infile name or end of name

		// main_outfile = xxx.S from main.infile = xxx.anything
		char * name = (char *)malloc( dot + 3 );
		for (i = 0; i < dot; i++) name[i] = main_infile[i];
		name[dot] = '.';
		name[dot + 1] = 'S';
		name[dot + 2] = '\0';
		main_outfile = name;
		
		// =BUG= the above logic makes no use of cool stuff in string.h
	}

	// initialize all the subsystems
	lex_open( main_infile );
	// =BUG= must initialize code generator to use main_outfile

	// and finally, compile the program
	Program * p = Program::compile();
	// =BUG= we don't seem to need the return value
}
