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

#######
# primary make target:  the Kestrel compiler

kestrel: main.o lexical.o
	$(COMPILER) -o kestrel main.o lexical.o

main.o: main.c lexical.h
	$(COMPILER) -c main.c

lexical.o: lexical.c lexical.h errors.h symboltable.h stringpool.h config.h
	$(COMPILER) -c lexical.c

symboltable.o: symboltable.c symboltable.h stringpool.h errors.h config.h
	$(COMPILER) -c symboltable.c

stringpool.o: stringpool.c stringpool.h errors.h config.h
	$(COMPILER) -c stringpool.c

errors.o: errors.c errors.h
	$(COMPILER) -c errors.c

#######
# secondary make target:  testlex for testing lexical.o

testlex: testlex.o lexical.o symboltable.o stringpool.o errors.o
	$(COMPILER) -o testlex testlex.o lexical.o symboltable.o stringpool.o errors.o

testlex.o: testlex.c lexical.h
	$(COMPILER) -c testlex.c

#######
# secondary make target:  clean for cleaning up the project

clean:
	rm *.o
	rm testlex
	rm kestrel
