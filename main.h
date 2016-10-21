/* main.h -- global variables exported by the main program */

/* Author: Douglas W. Jones
 * Date 8/30/2016 -- pasted from Lecture 17 with pro-forma improved comments
 */

/* Prerequisites for use:
 *   In main.c, but nowhere else,
 *     EXTERN must be defined first
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

/* Information from the command line */

EXTERN const char * main_progname; /* program name */
EXTERN const char * main_infile;   /* input file name, NULL if stdin */
EXTERN const char * main_outfile;  /* output file name, NULL if stdout */

/* any additional command line option values go here */

#undef EXTERN
