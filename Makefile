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
CFLAGS = -g -Wall -Wextra -Wparentheses -Wshadow -Wdouble-promotion -Winline -std=c++11 
#-Wlogical-not-parentheses

# set the default target to testlex. Kestral doesnt build yet
default_target: kestrel 
all: kestrel testlex

#######
# primary make target:  the Kestrel compiler

kestrel: main.o lexical.o lexsupport.o keywords.o symboltable.o stringpool.o \
	 errors.o \
	 program.o block.o declaration.o statement.o
	$(COMPILER) $(CFLAGS) -o kestrel main.o lexical.o lexsupport.o keywords.o \
				symboltable.o stringpool.o errors.o \
				program.o block.o declaration.o statement.o

main.o: main.cpp main.h lexical.h errors.h program.h config.h
	$(COMPILER) $(CFLAGS)  -c main.cpp

lexical.o: lexical.cpp lexical.h errors.h stringpool.h config.h symboltable.h \
	   keywords.h
	$(COMPILER) $(CFLAGS)  -c lexical.cpp

symboltable.o: symboltable.cpp symboltable.h stringpool.h errors.h config.h
	$(COMPILER) $(CFLAGS)  -c symboltable.cpp

stringpool.o: stringpool.cpp stringpool.h errors.h config.h
	$(COMPILER) $(CFLAGS)  -c stringpool.cpp

errors.o: errors.cpp errors.h
	$(COMPILER) $(CFLAGS)  -c errors.cpp

lexsupport.o: lexsupport.cpp lexsupport.h lexical.h sets.h errors.h
	$(COMPILER) $(CFLAGS)  -c lexsupport.cpp

keywords.o: keywords.cpp keywords.h errors.h symboltable.h stringpool.h config.h
	$(COMPILER) $(CFLAGS)  -c keywords.cpp

#######
# secondary make target:  testlex for testing lexical.o

testlex: testlex.o lexical.o stringpool.o errors.o symboltable.o lexsupport.o
	$(COMPILER) $(CFLAGS)  -o testlex testlex.o lexical.o stringpool.o errors.o symboltable.o lexsupport.o

testlex.o: testlex.cpp lexical.h
	$(COMPILER) $(CFLAGS)  -c testlex.cpp

#######
# secondary make target:  clean for cleaning up the project

clean:
	rm -f *.o
	rm -f testlex
	rm -f kestrel
	rm -rf CMakeFiles
	rm -f CMakeCache.txt
