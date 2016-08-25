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
    fprintf(handler, "#comments\n");

    //image size
    fprintf(handler, "%d %d\n",pxlCountX,pxlCountY);

    // rgb component depth
    fprintf(handler, "%d\n",49); // TODO new file color 50
	
    fprintf(handler, "%s",pgmMatrix); // TODO new file matrix

	fclose(handler);

}