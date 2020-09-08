#include "general.h"

//function checking if memory allocation succeed
void checkMemory(void* value, int line)
{
	if (value == NULL)
	{
		printf("Memory not avaliable in line %d!", line);
		exit(1);
	}
}

//function frees SingleSourceMovesTree
void freeTree(SingleSourceMovesTree t)
{
	freeTreeRec(t.source);
}

void freeTreeRec(SingleSourceMovesTreeNode *root)
{
	if (root == NULL)
		return;

	freeTreeRec(root->next_move[0]);
	freeTreeRec(root->next_move[1]);
	free(root->pos);
	free(root);
}

//function frees SingleSourceMovesList
void freeSingleSourceMovesList(SingleSourceMovesList *lst)
{
	SingleSourceMovesListCell *curr = lst->head;
	SingleSourceMovesListCell *next;

	while (curr)
	{
		next = curr->next;
		free(curr->position);
		free(curr);
		curr = next;
	}
	lst->head = lst->tail= NULL;

}

//function frees MultipleSourceMovesList
void freeMultipleSourceMovesList(MultipleSourceMovesList *lst)
{
	MultipleSourceMovesListCell *curr = lst->head;
	MultipleSourceMovesListCell *next;

	while (curr)
	{
		next = curr->next;
		freeSingleSourceMovesList(curr->single_source_moves_list);
		free(curr);
		curr = next;
	}
	lst->head = lst->tail = NULL;

}



//function prints board
void printBoard(Board board)
{
	printf("+-+-+-+-+-+-+-+-+-+ \n+ |1|2|3|4|5|6|7|8|\n+-+-+-+-+-+-+-+-+-+ \n");
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		printf("|%c", (char)('A' + i));
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("|%c", board[i][j]);
		printf("| \n+-+-+-+-+-+-+-+-+-+ \n");
	}

	printf("\n");
}

//function reset board to start position = ready to play
void resetBoardToStartPosition(Board board)
{
	int i, j, colStartFrom = 0;
	for (i = 0; i < 3; i++)//updating position of T-player
	{
		if (i % 2 == 0)
			colStartFrom = 1;
		for (j = colStartFrom; j < BOARD_SIZE; j += 2)
			board[i][j] = 'T';
		colStartFrom = 0;
	}

	for (i = 0; i < 3; i++) //updating position of B-player

	{
		if (i % 2 != 0)
			colStartFrom = 1;
		for (j = colStartFrom; j < BOARD_SIZE; j += 2)
			board[BOARD_SIZE - 1 - i][j] = 'B';
		colStartFrom = 0;
	}
}