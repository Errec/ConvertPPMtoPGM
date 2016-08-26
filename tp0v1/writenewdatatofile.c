#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"


void printBWdataToFile(FILE *handler) {

    //write the header file
    //image format
    fprintf(handler, "P2\n");

    //comments
    fprintf(handler, "#conversion By TP0 AEDS II UFMG 2016: Raniro Coelho\n");

    //image size
    fprintf(handler, "%d %d\n",pxlCountX,pxlCountY);

    // grey shades
    fprintf(handler, "%d\n",49); // TODO new file color 50
	
    fprintf(handler, "%s",pgmMatrix); // TODO new file matrix

	fclose(handler);

}