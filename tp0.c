// [123 234 206 14 81 220]  [123 123 123 206 206 206] 
// [22 208  198 192 51 99]  [22  22   22 192 192 192]

#include <stdio.h>

int main(){

	int imgOriginal[2][6] = {{123, 234, 56, 14, 81, 220} , 
							 {22, 208, 198, 192, 51, 99}};
	// TODO: malloc: int imgBW[3];
	// TODO: readPPM(input);
	int lines = 2;
	int columns = 6;

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j = j + 3)
		{
			// TODO: convertRGBToBW(imgOriginal[i][j]);
			// Y = (49 / 255 * (0.3 * R + 0.59 * G + 0.11 * B))
			printf("%d  ",imgOriginal[i][j]);
			printf("%d  ",imgOriginal[i][j+1]);
			printf("%d  ",imgOriginal[i][j+2]);
		}
		printf("\n");
	}
	
	return 0;
	// TODO: convertRGBToBW(int R, int G, int B);
	// TODO: writePGM();
}