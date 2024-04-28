PROJECT_NAME=tictactoe

# Compiler
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic

CC_FLAG_FPGA=-lintelfpgaup

#
# Compilation
#
all: $(PROJECT_NAME)

$(PROJECT_NAME): tictactoe.o draw.o mouse.o
	$(CC) -o tictactoe tictactoe.o draw.o mouse.o

tictactoe.o: tictactoe.c draw.h mouse.h
	$(CC) tictactoe.c -o tictactoe.o $(CC_FLAGS)

draw.o: draw.c draw.h
	$(CC) -o draw.o draw.c $(CC_FLAGS)

mouse.o: mouse.c mouse.h
	$(CC) -o mouse.o mouse.c $(CC_FLAGS)

clean:
	\rm -rf *.o *~ tictactoe
