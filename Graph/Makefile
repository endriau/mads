OBJ		= graph.o main.o
SRC		= graph.c main.c
EXE		= testGraph


CC		= gcc
CDEFS	= -Wall -O2


testGraph: $(OBJ) Makefile
	$(CC)    $(CDEFS) -o $(EXE) $(OBJ)


clean:
	rm -f $(OBJ) $(EXE)


clobber:
	rm -f $(EXE)


memcheck:
	valgrind --leak-check=full ./$(EXE)

