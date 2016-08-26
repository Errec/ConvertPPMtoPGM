/* 
 * This function opens a PPM file for reading using fgets(,,stdin)
 * which is used to try to open the file. 
 * Returns error message if it is not found and ask the user to quit
 * or reinsert the file name.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

#define MAX_FILENAME_SIZE 50

FILE openFileFromKeyboardInput(FILE *handler) {

	bool done = false; // while loop confirmation
	int index; // used in the file name array

	char *ppmFileName = malloc (MAX_FILENAME_SIZE);
    if (ppmFileName == NULL) {
        printf ("No memory\n");
        return 1;
    }

	printf("\n\nEnter the Name of the Image File:");

	while (!done) {
		
		fgets(ppmFileName, MAX_FILENAME_SIZE, stdin); // using fgets() for buffer overflow protection - reference http://stackoverflow.com/a/3302594

		// Remove new line, if we get one from the user
		index = strlen(ppmFileName)-1;
		if( ppmFileName[index] == '\n') {
		  ppmFileName[index] = '\0';
		}

		handler = fopen(ppmFileName, "rb"); 

		if(strcmp("Q",ppmFileName) == 0 || strcmp("q",ppmFileName) == 0) { 
			printf("\n...End of program...\n");
			exit(1);
		}
		else {
			if(handler == NULL) {
				fprintf(stderr, "\nFile not found! Try again or Q to quit:");
			}
			else {
				done = true;
			}
		}	
	}

	return handler; // return the PPM file
}