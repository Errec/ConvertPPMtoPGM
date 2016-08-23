// [123 234 206 14 81 220]  [123 123 123 206 206 206] 
// [22 208  198 192 51 99]  [22  22   22 192 192 192]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100

int main(int argC, char *argV[]){

	int index = 0;
	int lines = 0;
	int columns = 0;
	// Alocate memory + check for null
	char *fileName = malloc (MAX_NAME_SIZE);
    if (fileName == NULL) {
        printf ("No memory\n");
        return 1;
    }
	printf("\n\nEnter the Name of the Image File:");

	// using fgets() for buffer overflow protection - reference http://stackoverflow.com/a/3302594
	fgets(fileName, MAX_NAME_SIZE, stdin);

	// Remove new line, if we get one
	index = strlen(fileName)-1;
	if( fileName[index] == '\n') {
	  fileName[index] = '\0';
	}

	printf("This is your file: %s", fileName, "\n");

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
	}
	
	free (fileName);
	return 0;
	// TODO: convertRGBToBW(int R, int G, int B);
	// TODO: writePGM();
}