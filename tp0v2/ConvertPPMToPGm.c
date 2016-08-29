#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

#define MAX_FILENAME_SIZE 50

int pxlCountX;  // number of pixels in X
int pxlCountY;  // number of pixels in Y
int maxColor; // color depth
double bwValue; // hold the RGB converted B&W value
FILE *handler;
char *ppmCopy; // array with all the original RGB colors
char *pgmMatrix;  // a formated char array with all color values

/*
 * Function openPPMFileKeyboardInput
 * ----------------------------------
 * This function opens a PPM file for reading using fgets(,,stdin)
 * which is used to try to open the file.
 * Returns error message if it is not found and ask the user to quit
 * or reinsert the file name.
 */
void openPPMFileKeyboardInput() {

  bool done = false; // while loop check
  int index; // used in the file name array

  char *ppmFileName = malloc (MAX_FILENAME_SIZE);
    if (ppmFileName == NULL) {
        printf ("No memory\n");
        exit(1);
    }

  printf("\n\nEnter the Name of the PPM Image File:");

  while (!done) {

    fgets(ppmFileName, MAX_FILENAME_SIZE, stdin); // using fgets() for buffer overflow protection - reference http://stackoverflow.com/a/3302594

    // Remove new line, if we get one from the user
    index = strlen(ppmFileName) - 1;
    if(ppmFileName[index] == '\n') {
      ppmFileName[index] = '\0';
    }

    handler = fopen(ppmFileName, "rb");

    if(strcmp("Q", ppmFileName) == 0 || strcmp("q", ppmFileName) == 0) {
      printf("\n...End of program...\n");
      exit(1);
    }
    else {
      if(handler == NULL) {
        fprintf(stderr, "\nFile not found! Try again or (Q)Quit:");
      }
      else {
        done = true;
      }
    }
  }
  free(ppmFileName);
}

/*
 * Function  extractRGBvalues
 * --------------------------
 * This function check the format validity of PPMs files
 * received as argument and access required data to create
 * a new PMG file: the pixel density XY and the pixel data matrix.
 * The original PPM file is filtered to facilitate the process:
 * empty lines and comments are removed
 */
void extractRGBvalues() {

    int headLineCount = 1;  // used to track the current line in the file header
    int headLinesNum = 3; // max number of lines presents in a head without comments or empty lines
    int colorDataLineCount = 1; //  used to check when the color array begins
    int matrixLineSize = pxlCountX * 4 * 3; // number of chars in a line of the color matrix
    char linebuf[20]; // keep the head lines information

    /* check if the image format is valid */
    while ( fgets(linebuf, sizeof linebuf, handler)
                && headLineCount <= headLinesNum) {

    if (*linebuf == '#' || *linebuf == '\n') {  // skip comments and empty lines
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

        case 2 :  // check the pixel density XY
          sscanf (linebuf, "%d %d", &pxlCountX,&pxlCountY);
          if (pxlCountX == 0 || pxlCountY == 0) {
            fprintf(stderr, "Invalid image format.\n");
            exit(1);
          }
          break;

        case 3 :  // check the default color depth 0-255
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
  int fsize = ftell(handler); // the total number of chars stored in file
  fseek(handler, 0, SEEK_SET);  //same as rewind(f);

  *ppmCopy = (char *) malloc(fsize + 1); // allocated memory to the size of the original file
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
  ppmCopy[strlen(ppmCopy) - 1] = '\0';  // insert end of string in the last position
  fclose(handler);
}

/*
 * convertToBW
 * -----------
 * This function convert the ppmCopy char array into a int array
 * apply the grayscale conversion equation and store the new values
 * in a char array
 */
void convertToBW() {

    int totalNumberOfColorComponents = pxlCountX * 3 * pxlCountY; // RGB values count
    int totalNumberOfChar = pxlCountX * 4 * pxlCountY;  // array's total number of char
    int bwShades = 49;  // lvl of shades to apply to the new B&W image
    int ppmCopyIntArray[totalNumberOfColorComponents];  // an Int array with the color values
    *pgmMatrix = (char *) malloc(totalNumberOfChar);
    char *token;  // used in strtok()
    char str[2];  // hold the Int value for sprintf() int-char[] conversion

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
  { // Y = (49 / 255 * (0.3 * R + 0.59 * G + 0.11 * B)) convert RGB to B&W
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
  free(ppmCopy);
}

/*
 * Function savePGMFileKeyboarInput
 * --------------------------------
 * This function opens a PGM file or creates a new one using fgets(,,stdin)
 * to insert the name from keyboard
 */
void savePGMFileKeyboarInput() {

  bool done = false; // while loop check
  int index; // used in the file name array

  char *pgmFileName = malloc (MAX_FILENAME_SIZE);
    if (pgmFileName == NULL) {
        printf ("No memory\n");
        exit(1);
    }

  printf("\n\nEnter the Name of the new PGM Image File: ");

  while (!done) {

    fgets(pgmFileName, MAX_FILENAME_SIZE, stdin); // using fgets() for buffer overflow protection - reference http://stackoverflow.com/a/3302594

    // Remove new line, if we get one from the user
    index = strlen(pgmFileName)-1;
    if(pgmFileName[index] == '\n') {
      pgmFileName[index] = '\0';
    }

    handler = fopen(pgmFileName, "wb");

    if(handler != NULL && strcmp("Q",pgmFileName) == 0
               && strcmp("q",pgmFileName) == 0
               && strcmp("R",pgmFileName) == 0
               && strcmp("r",pgmFileName) == 0) {
        fprintf(stderr, "\nThis file already exists.\n\nEnter a new name or Replace(R) / Quit(Q): ");
    }

    if(strcmp("Q",pgmFileName) == 0 || strcmp("q",pgmFileName) == 0) {
      printf("\n\t...End of program.\n");
      exit(1);
    }

    if(strcmp("R",pgmFileName) == 0 || strcmp("r",pgmFileName) == 0) {
      done = true;
    }
  }
  free(pgmFileName);
}


/*
 * printBWdataToFile
 * -----------------
 * This function writes the new head values and the matrix of colors in a new file
 */
void printBWdataToFile() {

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
  free(pgmMatrix);
}
