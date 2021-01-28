#include "general.h"


//-----------------------------------q6----------------------------------//

//function is reading from binary-file board's situation and load the board to screen
void LoadBoard(char *filename, Board board)
{
	FILE *fp = fopen(filename, "rb");
	unsigned short int square, mask = 0xC000;
	int row = 0, col = 0;
	while (ftell(fp) < 16)
	{
		//reading unsigned short int from binary-file
		fread(&square, sizeof(unsigned short int), 1, fp);

		for (col = 0; col < BOARD_SIZE; col++)
		{
			unsigned short int x = (square&(mask >> col * 2)) >> (14 - col * 2);
			
			if (x == 1) //'01' represents T_CELL player
				board[row][col] = T_CELL;
			else if (x == 2) //'10' represents B_CELL player
				board[row][col] = B_CELL;
			else
				board[row][col] = EMPTY_CELL;
		}

		row++;
	}

	fclose(fp);

}
