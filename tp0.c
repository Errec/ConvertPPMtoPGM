#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILENAME_SIZE 50

int main(int argC, char *argV[]) {

// ------------------ part 1 : input filne name and check for NULL ------------------------------

	FILE *handler;
	char *buffer = NULL;
	int index = 0;
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
//  ------------------------------ END of part 1 ---------------------------------------- return my file handler
//  
//  ------------------------------Part 2: extract a string from that handler , remove comment lines starting with # ----------------



	// TODO: use malloc to set the sizes of line and s , rename variables
    int headLineCount = 1;
    int pxlCountX;
    int pxlCountY;
    int maxColor;
    int headLinesNum = 3;
    char linebuf[20];

    while ( fgets(linebuf, sizeof linebuf, handler) && headLineCount <= headLinesNum) {

		if (*linebuf == '#' || *linebuf == '\n') {
		continue;
		}
		else {

			switch(headLineCount) {

				case 1 :
					if (linebuf[0] != 'P' || linebuf[1] != '3') {
						fprintf(stderr, "Invalid image format.\n");
						exit(1);
					}
					break;

				case 2 :
					sscanf (linebuf,"%d %d",&pxlCountX,&pxlCountY);
					if (pxlCountX == 0 || pxlCountY == 0) {
						fprintf(stderr, "Invalid image format.\n");
						exit(1);
					}
					break;

				case 3 :
					sscanf (linebuf,"%d",&maxColor);
					if (maxColor <= 0 || maxColor > 255) {
						fprintf(stderr, "Invalid image format.\n");
						exit(1);
					}
					break;
			}
		}
		headLineCount++;
    }

    /* printf(" %d ",pxlCountX);
    printf(" %d ",pxlCountY);
    printf(" %d ",maxColor);
	*/

    int colorDataLine = 4;
    int colorDataLineCount = 1;
    int matrixLineSize = pxlCountX * 4 * 3;

    fseek(handler, 0, SEEK_END);
	int fsize = ftell(handler);
	fseek(handler, 0, SEEK_SET);  //same as rewind(f);

	char *ppmCopy = (char *) malloc(fsize + 1);
	char *currentLine = (char *) malloc(matrixLineSize + 1);
    

    while ( fgets(currentLine, matrixLineSize + 1, handler)) {
		if (*currentLine == '#' || *currentLine == '\n') {
		continue;
		}
		else {
			if(colorDataLineCount >= colorDataLine) {
				currentLine[strlen(currentLine) - 1] = ' ';
				strcat(ppmCopy,currentLine);
			}
			colorDataLineCount++;
		}
    }
    ppmCopy[strlen(ppmCopy) - 1] = '\0';
    printf("\n%s\n",ppmCopy);


    // -----------------------------------------END of part 2 ------------------------------------------------------------
    // 
    // ----------------------------------------- Part 3: convert the result string using the grayscale method -----------------
    int totalNumberOfColorValues = pxlCountX * 3 * pxlCountY;
    char* token;
    //int *ppmCopyIntArray = (int *)malloc(totalNumberOfColorValues);
    //char *pgmMatrix = (char *)malloc(pxlCountX * pxlCountY * 3 + 1);
    int ppmCopyIntArray[totalNumberOfColorValues];
    char pgmMatrix[10000];
	token = strtok(ppmCopy," ");   //think of it as substring, the part of the str before the comma
	for (int i = 0; i < totalNumberOfColorValues; i++)
	{
	    ppmCopyIntArray[i] = atoi(token);
	    // printf("%d ", ppmCopyIntArray[i]);
	            //i'm guessing the problem lies in one of the above two lines
	    token = strtok(NULL, " "); //this line is also required for tokenizing the next element
	}

	char str[2];
	double bwValue;
	int bwTemp;

	for (int i = 0; i < pxlCountX * pxlCountY * 3 - 2; i = i + 3)
	{
		bwValue = ((49.0 / 255.0) * ((0.3 * (double)ppmCopyIntArray[i]) + (0.59 * (double)ppmCopyIntArray[i + 1]) + (0.11 * (double)ppmCopyIntArray[i + 2])));
		bwTemp = bwValue;
		sprintf(str, "%d ", bwTemp);
		strcat(pgmMatrix,str);

		// strcpy(str, "  "); // duvida
		
		if (i % (pxlCountX * 3 - 3) == 0)
		{
			strcat(pgmMatrix,"\n");
		}
	}

	printf("%s" , pgmMatrix);
    // -----------------------------------------END of part 3 ------------------------------------------------------------
    //
  	//----------------------------------------Part 4 : open a new file and check -------------------------------------

    FILE *fp;
    //open file for output
    fp = fopen("teste.ppm", "wb");
    // -----------------------------------------END of part 4 ------------------------------------------------------------
    // 
  	//--------------------------part 5: write the converted array -------------------------------------------



    //write the header file
    //image format
    fprintf(fp, "P2\n");

    //comments
    fprintf(fp, "#comments\n");

    //image size
    fprintf(fp, "%d %d\n",pxlCountX,pxlCountY);

    // rgb component depth
    fprintf(fp, "%d\n",maxColor); // TODO new file color 50
	
    fprintf(fp, "%s\n",ppmCopy); // TODO new file matrix

	fclose(fp);





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
	free(currentLine);
    free(ppmCopy);
	fclose(handler);
	free (ppmFileName);
	// TODO: convertRGBToBW(int R, int G, int B);
	// TODO: writePGM();
	return 0;
}