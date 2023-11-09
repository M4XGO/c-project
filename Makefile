# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -pedantic

SRC = main.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = my_program

all: $(EXECUTABLE)
	@echo "Compilation succeeded. Run './$(EXECUTABLE)' to execute."

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXECUTABLE)
