#include "general.h"


//-----------------------------------q5----------------------------------//

//function is writing to binary-file board's situation
void StoreBoard(Board board, char *filename)
{
	FILE *fp = fopen(filename, "wb+");
	int row, col, bitLeftInRow = 16;
	unsigned short int line = 0, mask = 0x0001;

	printf("Writing to file...\n");

	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (col = 0; col < BOARD_SIZE; col++)
		{
			if (board[row][col] == T_CELL) //'01' represents T_CELL player
				line |= mask << (bitLeftInRow - 2);

			else if (board[row][col] == B_CELL) //'10' represents B_CELL player
				line |= mask << (bitLeftInRow - 1);

			bitLeftInRow -= 2;
		}

		//getting to end of specific row, reseting row's data and writing row data to binary file
		fwrite(&line, sizeof(unsigned short int), 1, fp);
		bitLeftInRow = 16;
		line = 0;
	}

	printf("All done!!\n");

	fclose(fp);
}