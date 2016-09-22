# Makefile

################################################################
# File dependencies for the Kestrel compiler                   #
# Author:  Douglas Jones                                       #
# Date:    8/29/2016 -- created                                #
# Date:    9/9/2016  -- incorporate stringpool & related       #
#                                                              #
# Instructions:                                                #
#          make         -- will build compiler someday         #
#          make testlex -- build lexical analysis test program #
#          make clean   -- delete everything unnecessary       #
################################################################

#######
# configuration options

# compiler to use, may give global compiler options here
COMPILER = c++

# compiler flags:
# -g  adds debuggin information
# -Wall turns on most warnings
# other warnings help dentify bugs. It is important to get rid of them or at least understand why they are there
CFLAGS = -g -Wall -Wextra -Wparentheses -Wshadow -Wdouble-promotion
#-Wlogical-not-parentheses

# set the default target to testlex. Kestral doesnt build yet
default_target: testlex
all: kestrel testlex

#######
# primary make target:  the Kestrel compiler

kestrel: main.o lexical.o
	$(COMPILER) $(CFLAGS) -o kestrel main.o lexical.o

main.o: main.c lexical.h
	$(COMPILER) $(CFLAGS)  -c main.c

lexical.o: lexical.c lexical.h errors.h stringpool.h config.h symboltable.h
	$(COMPILER) $(CFLAGS)  -c lexical.c

symboltable.o: symboltable.c symboltable.h stringpool.h errors.h config.h
	$(COMPILER) $(CFLAGS)  -c symboltable.c

stringpool.o: stringpool.c stringpool.h errors.h config.h
	$(COMPILER) $(CFLAGS)  -c stringpool.c

errors.o: errors.c errors.h
	$(COMPILER) $(CFLAGS)  -c errors.c

lexsupport.o: lexsupport.c lexsupport.h lexical.h sets.h
	$(COMPILER) $(CFLAGS)  -c lexsupport.c

#######
# secondary make target:  testlex for testing lexical.o

testlex: testlex.o lexical.o stringpool.o errors.o symboltable.o lexsupport.o
	$(COMPILER) $(CFLAGS)  -o testlex testlex.o lexical.o stringpool.o errors.o symboltable.o lexsupport.o

testlex.o: testlex.c lexical.h
	$(COMPILER) $(CFLAGS)  -c testlex.c

#######
# secondary make target:  clean for cleaning up the project

clean:
	rm -f *.o
	rm -f testlex
	rm -f kestrel
