/* 
 * This function convert the ppmCopy char array into a int array
 * apply the grayscale conversion equation and store the new values 
 * in a char array
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"


char convertToBW(char ppmCopy) {

    int totalNumberOfColorValues = pxlCountX * 3 * pxlCountY;
    int totalNumberOfChar = pxlCountX * 4 * pxlCountY;
    int bwShades = 49;
    int ppmCopyIntArray[totalNumberOfColorValues];
    char *token;
    char pgmMatrix[totalNumberOfChar];

	token = strtok(ppmCopy," "); 
	for (int i = 0; i < totalNumberOfColorValues; i++)
	{
	    ppmCopyIntArray[i] = atoi(token);
	    token = strtok(NULL, " "); 
	}

	char str[2];
	double bwValue;
	int bwTemp;

	for (int i = 0; i < pxlCountX * pxlCountY * 3; i += 3)
	{
		bwValue = (((double)bwShades / (double)maxColor) * 
				   ((0.3 * (double)ppmCopyIntArray[i]) + 
				   (0.59 * (double)ppmCopyIntArray[i+1]) + 
 				   (0.11 * (double)ppmCopyIntArray[i+2])));

		bwTemp = bwValue;
		
		if (i != 0 && i % (pxlCountX * 3) == pxlCountX * 3 - 3)
		{
			sprintf(str, "%d\n", bwTemp);
			strcat(pgmMatrix,str);
		}
		else {
			sprintf(str, "%d ", bwTemp);
			strcat(pgmMatrix,str);
		}
	}

	pgmMatrix[strlen(pgmMatrix) - 1] = '\0';
	return pgmMatrix;
}