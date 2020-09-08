#include "general.h"


//-----------------------------------q7----------------------------------//

//function playes full checkers game
void PlayGame(Board board, Player starting_player)
{
	printBoard(board);

	while (gameOver(board) != 1)
	{
		Turn(board, starting_player);
		starting_player = (starting_player == T_CELL ? B_CELL : T_CELL);
	}
}

/*function determine if game is over by 3 situation: one of 'T' player or 'B' player does not have
players on board OR one of 'T' player or 'B' reacheces to opposite-player first row */
int gameOver(Board board)
{
	int i, j, colStartFrom = 0, countB = 0, countT = 0;

	//checking case T_CELL reaches to row H or B_CELL reaches to row A
	if ((board[0][1] == B_CELL || board[0][3] == B_CELL || board[0][5] == B_CELL || board[0][7] == B_CELL) ||
		(board[7][0] == T_CELL || board[7][2] == T_CELL || board[7][4] == T_CELL || board[7][6] == T_CELL))
		return 1;

	//checking case that there are no players from one 'team' B or T on board 
	for (i = 1; i < BOARD_SIZE; i += 2)
	{
		if (i % 2 == 0)
			colStartFrom = 1;
		for (j = colStartFrom; j < BOARD_SIZE; j += 2)
		{
			countB += ((board[i][j] == B_CELL) ? 1 : 0);
			countT += ((board[i][j] == T_CELL) ? 1 : 0);
		}
		colStartFrom = 0;
	}

	if (countB == 0 || countT == 0)
		return 1;


	return 0;
}

