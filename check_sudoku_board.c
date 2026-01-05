#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* Returns 1 if and only if the 2D array of ints in board 
 * is in a valid Sudoku board state. Otherwise returns 0.
 *
 * DOES NOT PRODUCE ANY PRINTED OUTPUT
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: This function only requires that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 *  size: number of rows and columns in the board
 */
int valid_sudoku_board(int **board, int size) {
	if(board == NULL || size < 1 || size > 9){
		return 0;
	}
  // row
	for(int r = 0; r < size; r++){
		//create a new array
		int *seen = (int*)malloc(size*sizeof(int));
		if(seen == NULL){
			return 0;
		}

		//clear it
		for(int k = 0; k< size; k++){
			*(seen + k) = 0;
		}

		for(int c = 0; c < size; c++){
			int v = *(*(board+r)+c);
			if(v == 0) continue;
			int index = v-1;
			if(*(seen+index) == 1) {
				free(seen);
				return 0;
			}
			*(seen+index)=1;
		}
		free(seen);
	}

	//coloum
	for(int c = 0; c<size; c++){
		int *seen = (int*) malloc(size*sizeof(int));
		if(seen == NULL)return 0;

		//clear it
		for(int k = 0; k< size; k++){
			*(seen + k) = 0;
		}

		for(int r = 0; r<size; r++){
			int v = *(*(board+r)+c);
			if (v == 0) continue;
			int index = v-1;
			if(*(seen+index) == 1){
				free(seen);
				return 0;
			}
			*(seen+index) = 1;
		}
		free(seen);
	}
	return 1;   
}    
     
/* Read the first line of file to get the size of the board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whose address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line = NULL;
	size_t len = 0;

	// 'man getline' to learn about <stdio.h> getline
	if ( getline(&line, &len, fptr) == -1 ) {
		printf("Error reading the input file.\n");
		free(line);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line, DELIM); // 'man strtok' string tokenizer
	*size = atoi(size_chars);         // 'man atoi' alpha to integer
	free(line);                       // free memory allocated for line 
}


/* This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board with respect to rows and columns
 * only. It prints "invalid" (without quotes) if the input file is not valid.
 *
 * Usage: ./check_sudoku_board <input_filename>
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if file exists and is readable.
 * Exit with any non-zero result if unable to open and read a given file.
 */
int main( int argc, char **argv ) {              

	// Check if number of command-line arguments is correct.
	if(argc!=2){
		printf("Usage: ./check_sudoku_board <input_filename>\n");
		exit(1);
	}

	// Open the file 
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Can't open file for reading.\n");
		exit(1);
	}

	// will store the board's size, number of rows and columns
	int size;

	// Call get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);
	if (size < 1 || size > 9) {
    printf("invalid\n");      
		if (fclose(fp) != 0) {                
      printf("Error while closing the file.\n");
      exit(1);                          
    }
    return 0; 
}

	// Dynamically allocate a 2D array for given board size.
	// You must dyamically create an array of pointers to other arrays of ints
	int **board = (int**) malloc(size*sizeof(int*));
	if(board == NULL){
		printf("Error: malloc failed.\n");
		if (fclose(fp) != 0) {  
        printf("Error while closing the file.\n");
        exit(1);                         
    }
		exit(1);
	}
	for(int i = 0;i<size;i++){
		*(board + i) = (int *) malloc(size * sizeof(int));
		if(*(board+i)==NULL){
			printf("Error: malloc failed.\n");
			//free previous row
			for (int j = 0; j < i; j++) {
            free(*(board + j));
        }
			free(board);
			if (fclose(fp) != 0) { 
          printf("Error while closing the file.\n");
          exit(1);    
      }
      exit(1);
		}
	}

	// Read the remaining lines of the board data file.
	// Tokenize each line and store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		// read the line
		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading line %i of the file.\n", i+2);
			if (line) { free(line); line = NULL; } 
    	for (int r = 0; r < size; r++) {
        if (*(board + r)) free(*(board + r));
    	}
    	free(board);
    	if (fclose(fp) != 0) {                       
        printf("Error while closing the file.\n");
    	}
			exit(1);
		}

		token = strtok(line, DELIM);
		for (int j = 0; j < size; j++) {
			// TODO: Complete the line of code below
			int v = atoi(token);
			if (v < 0 || v > size) {
    		printf("invalid\n");
    		free(line);
    		for (int r = 0; r < size; r++) free(*(board + r));
    		free(board);
				if (fclose(fp) != 0) {
          printf("Error while closing the file.\n");
          exit(1);  
      }
    		return 0;
			}
			// to initialize elements of your 2D array.
			*(*(board + i) + j) = atoi(token); 
			token = strtok(NULL, DELIM);
		}
	}

	// Call valid_sudoku_board and print the appropriate
	//       output depending on the function's return value.
	int ok = valid_sudoku_board(board, size);
	printf(ok ? "valid\n" : "invalid\n");

	// TODO: Free dynamically allocated memory.
	for (int i = 0; i < size; i++) {
    free(*(board + i));   
	}
	free(board);
	if (line) { free(line); line = NULL; }

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file.\n");
		exit(1);
	} 

	return 0;       
}       // 202509

