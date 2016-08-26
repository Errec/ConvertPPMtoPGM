/* 
 * This function writes the new head values and the matrix of colors in a new file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void printBWdataToFile(FILE *handler, char *pgmMatrix, int pxlCountX, int pxlCountY) {

    // write image format
    fprintf(handler, "P2\n");

    // write author comment
    fprintf(handler, "#conversion By TP0 AEDS II UFMG 2016: Raniro Coelho\n");

    // write XY image pixel size
    fprintf(handler, "%d %d\n", pxlCountX, pxlCountY);

    // write grey shades value
    fprintf(handler, "%d\n", 49); // TODO new file color 50
	
    // write the B&W values matrix XY
    fprintf(handler, "%s", pgmMatrix); 

	fclose(handler);
}