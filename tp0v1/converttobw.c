/* 
 * This function convert the ppmCopy char array into a int array
 * apply the grayscale conversion equation and store the new values 
 * in a char array
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


char convertToBW(char ppmCopy, int pxlCountX, int pxlCountY, int maxColor) {

    int totalNumberOfColorComponents = pxlCountX * 3 * pxlCountY;	// RGB values count
    int totalNumberOfChar = pxlCountX * 4 * pxlCountY;	// array's total number of char
    int bwShades = 49;	// lvl of shades to apply to the new B&W image 
    int ppmCopyIntArray[totalNumberOfColorComponents];	// an Int array with the color values
    double bwValue;	// hold the RGB converted B&W value
    char pgmMatrix[totalNumberOfChar];	// a formated char array with all color values
    char *token;	// used in strtok()
    char str[2];	// hold the Int value for sprintf() int-char[] conversion 	

    /*
     * strtok() and atoi() to remove the Int values to ppmCopyIntArray[]
     */
	token = strtok(ppmCopy, " "); 
	for (int i = 0; i < totalNumberOfColorComponents; i++)
	{
	    ppmCopyIntArray[i] = atoi(token);
	    token = strtok(NULL, " "); 
	}

	for (int i = 0; i < totalNumberOfColorComponents; i += 3)
	{	// Y = (49 / 255 * (0.3 * R + 0.59 * G + 0.11 * B)) convert RGB to B&W
		bwValue = (((double)bwShades / (double)maxColor) * 
				   ((0.3 * (double)ppmCopyIntArray[i]) + 
				   (0.59 * (double)ppmCopyIntArray[i+1]) + 
 				   (0.11 * (double)ppmCopyIntArray[i+2])));
		// insert new line every X Ints
		if (i != 0 && i % (pxlCountX * 3) == pxlCountX * 3 - 3)
		{
			sprintf(str, "%d\n", bwValue);
			strcat(pgmMatrix, str);
		}
		else {
			sprintf(str, "%d ", bwValue);
			strcat(pgmMatrix,str);
		}
	}

	pgmMatrix[strlen(pgmMatrix) - 1] = '\0'; // insert end of string in the last position
	
	return pgmMatrix; // retur formated PGM colors array
}