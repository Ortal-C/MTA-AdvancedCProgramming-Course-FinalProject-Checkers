#include "general.h"


//-----------------------------------q4----------------------------------//

//function does a turn
void Turn(Board board, Player player)
{
	int side, max = 0;
	MultipleSourceMovesList *multiList;

	//finding all possible moves
	multiList = FindAllPossiblePlayerMoves(board, player);

	//checking which MultipleSourceMovesListCell has more benefit
	MultipleSourceMovesListCell *maxCell = FindMaxMultiCell(*multiList, &max);
	SingleSourceMovesListCell *currMove = maxCell->single_source_moves_list->head;
	SingleSourceMovesListCell *afterMove = maxCell->single_source_moves_list->head->next;

	int dir = ((player == T_CELL) ? 1 : (-1)); //defining row direction: top-down or bottom-up

	while (afterMove != NULL)
	{
		board[currMove->position->row - '0'][currMove->position->col - '0'] = EMPTY_CELL; //removing current cell data
		board[afterMove->position->row - '0'][afterMove->position->col - '0'] = player; //placing player in it's new position

		if (afterMove->captures != 0)
		{
			//If we eat a player which it is on the left
			if (afterMove->position->col - '0' > currMove->position->col - '0')
				side = 1 * dir;
			//If we eat a player which it is on the right
			if (afterMove->position->col - '0' < currMove->position->col - '0')
				side = (-1)*dir;

			//remove eaten player
			board[currMove->position->row - '0' + dir][currMove->position->col - '0' + side] = EMPTY_CELL; //removing current cell data
		}


		if (player == T_CELL)
			printf("player TOP_DOWN's turn\n");
		else
			printf("player BOTTOM_UP's turn\n");

		//printing move
		printf("%c%c->%c%c \n", currMove->position->row - '0' + 'A', currMove->position->col + 1, afterMove->position->row - '0' + 'A', afterMove->position->col + 1);
		//printing board
		printBoard(board);

		//keep traveling on SingleSourceMovesList
		currMove = afterMove;
		afterMove = afterMove->next;

	}
	freeMultipleSourceMovesList(multiList);
}

//function find which MultipleSourceMovesListCell has more benefit in given MultipleSourceMovesList
MultipleSourceMovesListCell* FindMaxMultiCell(MultipleSourceMovesList lst, int *max)
{
	int count = 0, MaxCaptures = 0, maxMoves = 0;

	// case there is not exist MultiList
	if (lst.head == NULL)
		return NULL;

	else
	{
		MultipleSourceMovesListCell *currCell = lst.head;
		MultipleSourceMovesListCell *res = currCell;
		while (currCell != NULL) //traveling on cells in MultipleSourceMovesList
		{
			SingleSourceMovesListCell* currSingle = currCell->single_source_moves_list->head;
			while (currSingle != NULL) //traveling on cells in SingleSourceMovesList and count number of moves
			{
				count++;
				currSingle = currSingle->next;
			}

			// top priority: if the player can eat it's opposite-player
			if (MaxCaptures < currCell->single_source_moves_list->tail->captures)
			{
				MaxCaptures = currCell->single_source_moves_list->tail->captures;
				res = currCell;
			}

			else if (MaxCaptures == 0)
			{
				if (count > maxMoves)
				{
					maxMoves = count;
					res = currCell;
				}
			}

			count = 0;
			currCell = currCell->next;
		}

		return res;
	}
}
