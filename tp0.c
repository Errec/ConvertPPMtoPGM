#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILENAME_SIZE 100

int main(int argC, char *argV[]) {
	FILE *handler;
	char *buffer = NULL;
	int index = 0;
	int lines = 0;
	int columns = 0;
	bool done = false;
	// Alocate memory + check for null
	char *ppmFileName = malloc (MAX_FILENAME_SIZE);
    if (ppmFileName == NULL) {
        printf ("No memory\n");
        return 1;
    }
	printf("\n\nEnter the Name of the Image File:");

	while (!done) {
		// using fgets() for buffer overflow protection - reference http://stackoverflow.com/a/3302594
		fgets(ppmFileName, MAX_FILENAME_SIZE, stdin);

		// Remove new line, if we get one
		index = strlen(ppmFileName)-1;
		if( ppmFileName[index] == '\n') {
		  ppmFileName[index] = '\0';
		}

		handler = fopen(ppmFileName, "r");

		if(strcmp("Q",ppmFileName) == 0) {
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








    char line[50] = "";
    char s1[200] = "";
    char s[200] = "";

    while ( fgets(line, sizeof line, handler) )
    {
        if (*line == '#')
            continue;
        strcat(s , line);
    }


    printf("%s",s);







    fclose(handler);

	//buffer = (char*) malloc(sizeof(char) * (string_size + 1));

	/*
	int imgOriginal[2][6] = {{123, 234, 56, 14, 81, 220} , 
							 {22, 208, 198, 192, 51, 99}};
	// TODO: malloc: int imgBW[3];
	// TODO: readPPM(input);
	lines = 2;
	columns = 6;

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j = j + 3)
		{
			// TODO: convertRGBToBW(imgOriginal[i][j]);
			// Y = (49 / 255 * (0.3 * R + 0.59 * G + 0.11 * B))
			printf("%d  ",imgOriginal[i][j]);
			printf("%d  ",imgOriginal[i][j+1]);
			printf("%d  ",imgOriginal[i][j+2]);
		}
		printf("\n");
	} */
	
	free (ppmFileName);
	return 0;
	// TODO: convertRGBToBW(int R, int G, int B);
	// TODO: writePGM();
}