#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

FILE openFileFromKeyboardInput(FILE *handler); 
char extractRGBvaluesFromFile(FILE *handler);
char convertToBW(char ppmCopy);
FILE saveNewFile(FILE *handler);
void printBWdataToFile(FILE *handler);

#endif