#
# Makefile
#
# This file automates the
# compilation process and
# file dependencies.It also
# provides commands for memory
# checks via valgrind.
#
# @author:	Endri Kastrati
# @date:	22/11/2016
#



OBJ = main.o sort.o stack.o
SRC = main.c sort.c stack.c
EXE = testing

CC  	= gcc
CFLAGS 	= -Wall -O2


testing: $(OBJ) Makefile
	$(CC) $(CFLAGS)   -o $(EXE) $(OBJ)


clean:
	rm -f $(OBJ) $(EXE)


sort.o: sort.h Makefile
main.o: sort.h Makefile



