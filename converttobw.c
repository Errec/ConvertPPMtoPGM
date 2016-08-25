#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"


char convertToBW(char ppmCopy) {

    int totalNumberOfColorValues = pxlCountX * 3 * pxlCountY;
    int totalNumberOfChar = pxlCountX * 4 * pxlCountY;
    char* token;

    int ppmCopyIntArray[totalNumberOfColorValues];
    char pgmMatrix[totalNumberOfChar];
	token = strtok(ppmCopy," ");   //think of it as substring, the part of the str before the comma
	for (int i = 0; i < totalNumberOfColorValues; i++)
	{
	    ppmCopyIntArray[i] = atoi(token);
	    token = strtok(NULL, " "); //this line is also required for tokenizing the next element
	}

	char str[2];
	double bwValue;
	int bwTemp;

	for (int i = 0; i < pxlCountX * pxlCountY * 3; i += 3)
	{
		bwValue = ((49.0 / 255.0) * ((0.3 * (double)ppmCopyIntArray[i]) + 
									 (0.59 * (double)ppmCopyIntArray[i + 1]) + 
									 (0.11 * (double)ppmCopyIntArray[i + 2])));
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