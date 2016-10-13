# Makefile

################################################################
# File dependencies for the Kestrel compiler                   #
# Author:  Douglas Jones                                       #
# Date:    8/29/2016 -- created                                #
# Date:    9/9/2016  -- incorporate stringpool & related       #
# Date:    9/23/2016 -- incorporate keywords & related         #
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

kestrel: main.o lexical.o keywords.o symboltable.o stringpool.o errors.o \
	 program.o block.o
	$(COMPILER) -o kestrel main.o lexical.o keywords.o \
			symboltable.o stringpool.o errors.o \
			program.o block.o

main.o: main.cpp main.h lexical.h errors.h program.h config.h
	$(COMPILER) -c main.cpp

####
# primary make target:  the Kestrel compiler, lexical subsection

lexical.o: lexical.c lexical.h errors.h keywords.h symboltable.h \
	   stringpool.h config.h
	$(COMPILER) -c lexical.c

lexsupport.o: lexsupport.o lexical.h errors.h
	$(COMPILER) -c lexsupport.c

keywords.o: keywords.c keywords.h errors.h symboltable.h stringpool.h config.h
	$(COMPILER) -c keywords.c

symboltable.o: symboltable.c symboltable.h stringpool.h errors.h config.h
	$(COMPILER) -c symboltable.c

stringpool.o: stringpool.c stringpool.h errors.h config.h
	$(COMPILER) -c stringpool.c

errors.o: errors.c errors.h main.h config.h
	$(COMPILER) -c errors.c

####
# primary make target:  the Kestrel compiler, parser subsection

program.o: program.cpp program.h sets.h errors.h lexical.h lexsupport.h \
	   block.h
	$(COMPILER) -c program.cpp

block.o: block.cpp block.h sets.h errors.h lexical.h lexsupport.h
	$(COMPILER) -c block.cpp


####
# primary make target:  the Kestrel compiler, code generator subsection

#######
# secondary make target:  testlex for testing lexical.o

testlex: testlex.o lexical.o keywords.o symboltable.o stringpool.o errors.o
	$(COMPILER) -o testlex testlex.o lexical.o keywords.o \
			symboltable.o stringpool.o errors.o

testlex.o: testlex.c lexical.h errors.h main.h config.h
	$(COMPILER) -c testlex.c

#######
# secondary make target:  clean for cleaning up the project

clean:
	rm *.o
	rm testlex
	rm kestrel
