#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

FILE openPPMFileKeyboardInput(FILE *handler); 
char extractRGBvalues(FILE *handler);
char convertToBW(char ppmCopy, int pxlCountX, int pxlCountY, int maxColor);
FILE savePGMFileKeyboarInput(FILE *handler);
void printBWdataToFile(FILE *handler, char *pgmMatrix, int pxlCountX, int pxlCountY);

#endif