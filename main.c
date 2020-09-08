#include "general.h"

int main()
{
	Board board = { EMPTY_CELL };

	resetBoardToStartPosition(board);
	PlayGame(board, 'T');

	system("pause");
}