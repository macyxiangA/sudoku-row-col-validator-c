
# Sudoku Board Validator (C)

This project provides a small C program that validates whether a Sudoku board state is valid with respect to rows and columns. The program reads a board from a CSV-formatted text file and prints either "valid" or "invalid".

Validation rules in this project focus on row and column constraints only. A board is considered valid if each row and each column contains only blanks (0) or digits in the range 1 to N (where N is the board size), and no digit appears more than once in any single row or column.

## What the Program Checks

The validator enforces the following constraints:

- Board size must be between 1 and 9
- Each cell value must be between 0 and N
- In every row, non-zero digits must not repeat
- In every column, non-zero digits must not repeat

This validator does not enforce subgrid constraints. It is intended as a focused checker for row and column validity.

## Repository Contents

- check_sudoku_board.c  
  Main program source file. Reads the input file, builds a 2D board in memory, validates it, prints the result, and frees memory.

- board*.txt  
  Example board inputs. These are comma-delimited rows with a size header line.

- invalid_board_file.txt  
  An example of an input file that should fail validation.

- check_sudoku_board  
  A compiled executable if built locally.

- board*solution.txt  
  Optional reference outputs if present in the folder.

## Input File Format

The input file is plain text with commas separating values.

Line 1 contains a single integer N representing the size of the board.

The next N lines contain N comma-separated integers per line.

Example:

    3
    1,0,0
    2,0,0
    3,0,1

In this format, 0 represents a blank cell.

## Build

Compile with a standard C compiler:

    gcc check_sudoku_board.c -o check_sudoku_board

## Run

Run the validator by passing an input file path:

    ./check_sudoku_board board0.txt

If the board is valid with respect to row and column rules, the program prints:

    valid

Otherwise, it prints:

    invalid

If the program is called with the wrong number of arguments, it prints a usage message.

## Implementation Notes

- The board is dynamically allocated as an array of row pointers, each pointing to an array of integers.
- Each row and column is checked using a temporary "seen" array of length N to detect duplicates.
- All allocated memory is freed before exit in both success and failure paths.

## Version Control Recommendations

The following files are build artifacts and should typically be excluded from version control:

- check_sudoku_board
- *.o
- *.i
- *.s

If you want a clean repository, include these in a .gitignore file.

## License

This project is intended for learning and demonstration purposes.

