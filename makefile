PROJECT_NAME=tictactoe

# Compiler
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic

#
# Compilation
#
all: $(PROJECT_NAME)

$(PROJECT_NAME): tictactoe.o draw.o
	$(CC) -o tictactoe tictactoe.o draw.o

tictactoe.o: tictactoe.c draw.h
	$(CC) tictactoe.c -o tictactoe.o $(CC_FLAGS)

draw.o: draw.c draw.h
	$(CC) -o draw.o draw.c $(CC_FLAGS)

clean:
	\rm -rf *.o *~ tictactoe
