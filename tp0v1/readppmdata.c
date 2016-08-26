/* 
 * This function check the format validity of PPMs files
 * received as argument and access required data to create 
 * a new PMG file: the pixel density XY and the pixel data matrix.
 * The original PPM file is filtered to facilitate the process:
 * empty lines and comments are removed 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

char extractRGBvalues(FILE *handler) {

    int headLineCount = 1;	// used to track the current line in the file header
    int pxlCountX;	// number of pixels in X
    int pxlCountY;	// number of pixels in Y
    int maxColor;	// color depth
    int headLinesNum = 3;	// max number of lines presents in a head without comments or empty lines
    int colorDataLineCount = 1; //  used to check when the color array begins
    int matrixLineSize = pxlCountX * 4 * 3;	// number of chars in a line of the color matrix
    char linebuf[20];	// keep the head lines information

    /* check if the image format is valid */
    while ( fgets(linebuf, sizeof linebuf, handler)
    	          && headLineCount <= headLinesNum) {

		if (*linebuf == '#' || *linebuf == '\n') {	// skip comments and empty lines
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

				case 2 :	// check the pixel density XY
					sscanf (linebuf, "%d %d", &pxlCountX,&pxlCountY);
					if (pxlCountX == 0 || pxlCountY == 0) {
						fprintf(stderr, "Invalid image format.\n");
						exit(1);
					}
					break;

				case 3 :	// check the default color depth 0-255
					sscanf (linebuf, "%d", &maxColor);
					if (maxColor <= 0 || maxColor > 255) {
						fprintf(stderr, "Invalid image format.\n");
						exit(1);
					}
					break;
			}
		}
		headLineCount++;
    }

    /*
    * get the file size as argument in the malloc function. The new array is used
    * to store the file content
    */
    fseek(handler, 0, SEEK_END);
	int fsize = ftell(handler);	// the total number of chars stored in file
	fseek(handler, 0, SEEK_SET);  //same as rewind(f);

	char *ppmCopy = (char *) malloc(fsize + 1);	// allocated memory to the size of the original file
	char *currentLine = (char *) malloc(matrixLineSize + 1); // number of chars in one line of X
    
    /*
    * fgets skip the comments and empty lines
    * only the color matrix is stored in a new array, ppmCopy
    */    
    while ( fgets(currentLine, matrixLineSize + 1, handler)) {
		if (*currentLine == '#' || *currentLine == '\n') {
		continue;
		}
		else {
			if(colorDataLineCount > colorDataLine) {
				currentLine[strlen(currentLine) - 1] = ' ';
				strcat(ppmCopy,currentLine);
			}
			colorDataLineCount++; // update the current line in the loop
		}
    }
    
    ppmCopy[strlen(ppmCopy) - 1] = '\0';	// insert end of string in the last position

    return ppmCopy;	// return a array with all the original RGB colors
}