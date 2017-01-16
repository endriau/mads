#
# Makefile for the testing
# procedures regarding the
# stack data structure.
#
# @author:	Endri Kastrati
# @date:	9/01/2017
#


# Using the gcc compiler with
# debugging and optimization
# flags enabled.Also linking
# to the path of the stack.h
# header file.
CC 		= gcc
CFLAGS	= -Wall -O2 -I../


# Declaring the source code and
# the object files to be generated
# as well as the name of the executable
# file.
SRC  = stackTest.c  ../stack.c 
OBJ  = stackTest.o ../stack.o
EXE  = stackTest




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
