CC = gcc
CFLAGS = -Wall -pedantic -ansi
BIN = ccl.exe
OBJ = main.o ccl.o pgm.o error.o set.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@
