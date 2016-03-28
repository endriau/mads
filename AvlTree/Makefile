OBJ = main.o tree.o
SRC = main.c tree.c
EXE = testTree

CC 		= gcc
CFLAGS 	= -Wall -O2


testTree: $(OBJ) Makefile
	$(CC) $(CFLAGS)   -o $(EXE) $(OBJ)


clean:
	rm -f $(OBJ) $(EXE)


memcheck:
	valgrind --leak-check=full ./$(EXE)
