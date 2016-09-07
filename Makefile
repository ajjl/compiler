# Makefile

################################################################
# File dependencies for the Kestrel compiler                   #
# Author:  Author's Names                                      #
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

lexical.o: lexical.c lexical.h errors.h
	$(COMPILER) -c lexical.c

errors.o: errors.c errors.h
	$(COMPILER) -c errors.c

#######
# secondary make target:  testlex for testing lexical.o

testlex: testlex.o lexical.o
	$(COMPILER) -o testlex testlex.o lexical.o

testlex.o: testlex.c lexical.h
	$(COMPILER) -c testlex.c

#######
# secondary make target:  clean for cleaning up the project

clean:
	rm *.o
	rm testlex
	rm kestrel
