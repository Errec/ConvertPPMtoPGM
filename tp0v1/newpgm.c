/* 
 * Function savePGMFileKeyboarInput
 * 
 * This function opens a PGM file or creates a new one using fgets(,,stdin) 
 * to insert the name from keyboard
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

#define MAX_FILENAME_SIZE 50

FILE savePGMFileKeyboarInput(FILE *handler) {

	bool done = false; // while loop check
	int index; // used in the file name array

	char *pgmFileName = malloc (MAX_FILENAME_SIZE);
    if (pgmFileName == NULL) {
        printf ("No memory\n");
        exit(1);
    }

	printf("\n\nEnter the Name of the new PGM Image File: ");

	while (!done) {
		
		fgets(pgmFileName, MAX_FILENAME_SIZE, stdin); // using fgets() for buffer overflow protection - reference http://stackoverflow.com/a/3302594

		// Remove new line, if we get one from the user
		index = strlen(pgmFileName)-1;
		if(pgmFileName[index] == '\n') {
		  pgmFileName[index] = '\0';
		}

		handler = fopen(pgmFileName, "wb"); 

		if(handler != NULL && strcmp("Q",pgmFileName) == 0 
						   && strcmp("q",pgmFileName) == 0
						   && strcmp("R",pgmFileName) == 0
						   && strcmp("r",pgmFileName) == 0) {
				fprintf(stderr, "\nThis file already exists.\n\nEnter a new name or Replace(R) / Quit(Q): ");
		}
		
		if(strcmp("Q",pgmFileName) == 0 || strcmp("q",pgmFileName) == 0) { 
			printf("\n\t...End of program.\n");
			exit(1);
		}

		if(strcmp("R",pgmFileName) == 0 || strcmp("r",pgmFileName) == 0) {
			done = true;
		}
	
	}

	return handler; // return the PGM file
}