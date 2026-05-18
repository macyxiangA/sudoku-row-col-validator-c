CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -pedantic

TARGET := check_sudoku_board

.PHONY: all test clean

all: $(TARGET)

$(TARGET): check_sudoku_board.c
	$(CC) $(CFLAGS) check_sudoku_board.c -o $(TARGET)

test: $(TARGET)
	./$(TARGET) board0.txt
	./$(TARGET) invalid_board_file.txt

clean:
	rm -f $(TARGET) *.o
