#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

#define MAX_FILENAME_SIZE 50

char extractRGBvalues(FILE *handler) {

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
    return ppmCopy;
}