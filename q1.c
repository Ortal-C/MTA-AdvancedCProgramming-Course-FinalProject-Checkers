#include "general.h"

//-----------------------------------q1----------------------------------//

SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{
	//there is no tree to return
	if (board == NULL)
		return NULL;

	//define player, opposite player and row direction: top-down or bottom-up
	Player currPlayer = board[src->row - '0'][src->col - '0'];
	Player oppPlayer = (currPlayer == T_CELL ? B_CELL : T_CELL);
	int dir = (currPlayer == T_CELL ? 1 : (-1)); // define direction (botom-up or top-down)

	//allocation for SingleSourceMovesTree
	SingleSourceMovesTree *tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkMemory(tree, __LINE__);

	int flag = NOMOVE;
	unsigned short captures = 0;

	tree->source = FindSingleSourceMovesHelper(board, src, flag, captures, currPlayer, oppPlayer, dir);
	return tree;
}

SingleSourceMovesTreeNode *FindSingleSourceMovesHelper(Board board, checkersPos *src, int flag, unsigned short captures, Player currPlayer, Player oppPlayer, int dir)
{
	int currRow = src->row - '0';
	int currCol = src->col - '0';

	//base case: the chosen cell is empty
	if ((board[currRow][currCol] != currPlayer) && (board[currRow][currCol] != oppPlayer))
		return NULL;

	SingleSourceMovesTreeNode *node = createMovesTreeNode(board, src, captures, NULL, NULL);
	checkersPos *L_pos = src, *R_pos = src;


	//the cell on left side of source is empty, can only move to left
	if ((currRow + 1 * dir >= 0 && currRow + 1 * dir < BOARD_SIZE) && (currCol - 1 >= 0 && currCol - 1 < BOARD_SIZE)
		&& (board[currRow + 1 * dir][currCol - 1] == EMPTY_CELL) && (flag == NOMOVE))
	{
		//updating board
		board[currRow][currCol] = 0; //removing player
		board[currRow + 1 * dir][currCol - 1] = currPlayer; //updating new position

		//updating new travel position
		L_pos = createCheckersPos(currRow + 1 * dir, currCol - 1);

		node->next_move[LEFT] = createMovesTreeNode(board, L_pos, captures, NULL, NULL);

		//reset board as it was
		board[L_pos->row - '0'][L_pos->col - '0'] = 0;
		board[currRow][currCol] = currPlayer;
	}

	//case cell on left is not empty, can eat oppPlayer
	else if ((board[currRow + 1 * dir][currCol - 1] == oppPlayer && flag != SINGLEMOVE)
		&& (currRow + 2 * dir >= 0 && currRow + 2 * dir < BOARD_SIZE) && (currCol - 2 >= 0 && currCol - 2 < BOARD_SIZE)
		&& (board[currRow + 2 * dir][currCol - 2] == EMPTY_CELL))
	{
		//updating board
		board[currRow][currCol] = 0; //removing player
		board[currRow + 2 * dir][currCol - 2] = currPlayer; //updating new position

		//updating new travel position
		L_pos = createCheckersPos(currRow + 2 * dir, currCol - 2);

		node->next_move[LEFT] = FindSingleSourceMovesHelper(board, L_pos, 2, captures + 1, currPlayer, oppPlayer, dir);

		//reset board
		board[L_pos->row - '0'][L_pos->col - '0'] = 0;
		board[currRow][currCol] = currPlayer;
	}
	else
		node->next_move[LEFT] = NULL;


	//the cell on right side of source is empty, can only move to right
	if ((currRow + 1 * dir >= 0 && currRow + 1 * dir < BOARD_SIZE) && (currCol + 1 >= 0 && currCol + 1 < BOARD_SIZE)
		&& (board[currRow + 1 * dir][currCol + 1] == EMPTY_CELL) && (flag == NOMOVE))
	{
		//updating board
		board[currRow][currCol] = 0; //removing player
		board[currRow + 1 * dir][currCol + 1] = currPlayer; //updating new position

		//updating new travel position
		R_pos = createCheckersPos(currRow + 1 * dir, currCol + 1);

		node->next_move[RIGHT] = createMovesTreeNode(board, R_pos, captures, NULL, NULL);

		//reset board
		board[R_pos->row - '0'][R_pos->col - '0'] = 0;
		board[currRow][currCol] = currPlayer;

	}
	//case cell on right is not empty, can eat oppPlayer or can't do anything
	else if ((board[currRow + 1 * dir][currCol + 1] == oppPlayer) && (flag != SINGLEMOVE)
		&& (currRow + 2 * dir >= 0 && currRow + 2 * dir < BOARD_SIZE) && (currCol + 2 >= 0 && currCol + 2 < BOARD_SIZE)
		&& (board[currRow + 2 * dir][currCol + 2] == EMPTY_CELL))
	{
		//updating board
		board[currRow][currCol] = 0; //removing player	
		board[currRow + 2 * dir][currCol + 2] = currPlayer; //updating new position

		//updating new travel position
		R_pos = createCheckersPos(currRow + 2 * dir, currCol + 2);

		node->next_move[RIGHT] = FindSingleSourceMovesHelper(board, R_pos, 2, captures + 1, currPlayer, oppPlayer, dir);

		//reset board
		board[R_pos->row - '0'][R_pos->col - '0'] = 0;
		board[currRow][currCol] = currPlayer;

	}
	else
		node->next_move[RIGHT] = NULL;

	return node;
}

//function creates SingleSourceMovesTreeNode from given board, position, captures and sons: left and right
SingleSourceMovesTreeNode* createMovesTreeNode(Board board, checkersPos *pos, unsigned short captures, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right)
{
	//memory allocation for new SingleSourceMovesTreeNode
	SingleSourceMovesTreeNode* node = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkMemory(node, __LINE__);

	memcpy(node->board, board, (BOARD_SIZE * BOARD_SIZE * sizeof(unsigned char)));
	node->pos = pos;
	node->total_captures_so_far = captures;
	node->next_move[0] = left;
	node->next_move[1] = right;

	return node;
}

//function creates checkers-position
checkersPos* createCheckersPos(int row, int col)
{
	//memory allocation for new position
	checkersPos* nodePos = (checkersPos*)malloc(sizeof(checkersPos));
	checkMemory(nodePos, __LINE__);

	//updating current position
	nodePos->row = row + '0';
	nodePos->col = col + '0';

	return nodePos;
}


/*	test: function prints tree (in-order)
void printTree(SingleSourceMovesTreeNode *root)
{
	if (!root)
		return;
	printTree(root->next_move[0]);
	printf("[%c][%c] ", 'A' + root->pos->row - '0', 1 + root->pos->col);
	printTree(root->next_move[1]);
}*/
