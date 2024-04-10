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

$(PROJECT_NAME): tictactoe.o
	$(CC) -o tictactoe tictactoe.o

tictactoe.o: tictactoe.c
	$(CC) tictactoe.c -o tictactoe.o  $(CC_FLAGS)

clean:
	\rm -rf *.o *~ tictactoe
