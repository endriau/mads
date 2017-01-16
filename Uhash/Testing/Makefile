#
# Makefile for testing the
# procedures regarding the
# universal hash function
# data structure.
#
# @author:	Endri Kastrati
# @date:	16/01/2017
#


# Using the gcc compiler with
# debugging and optimization
# flags enabled.Also linking
# to the path of the uhash.h
# header file.
CC		= gcc
CFLAGS	= -Wall -O2 -I../


# Declaring the source code
# and the object files to
# be generated as well as
# the name of the executable
# file.
SRC	= uhashTest.c ../uhash.c
OBJ = uhashTest.o ../uhash.o
EXE = uhashTest



# The first rule to be executed
# whenever the make command is
# issued with parameters.This
# rule generates the object codes
# and executable file associated
# with the given variable values.
Makefile: $(OBJ)
	$(CC) $(CFLAGS)   -o $(EXE) $(OBJ)



# This rule runs the executable
# generated during the compilation
# process.
test:
	./$(EXE)



# This rule runs the executable file
# with the valgrind program.It basically
# runs the executable and prints to the
# standard output any memory leak errors.
memcheck:
	valgrind --leak-check=full ./$(EXE)



# This rule removes the object files
# associated with the source files
# and the executable file as well.
clean:
	rm -f $(OBJ) $(EXE)


