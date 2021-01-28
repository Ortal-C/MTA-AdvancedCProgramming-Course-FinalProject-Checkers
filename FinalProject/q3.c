#include "general.h"


//-----------------------------------q3----------------------------------//

//function gets a player and finds all possible moves the player can do	and sums it in MultipleSourceMovesList
MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
	int i, j, colStartFrom = 0;
	//memory allocation for MultipleSourceMovesList
	MultipleSourceMovesList *lst = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkMemory(lst, __LINE__);
	*lst = makeEmptyMultiList();
	SingleSourceMovesTree *moves_Tree;
	checkersPos *currPos;

	//checking each board-cell data. if player is in the current cell we'll create MultipleSourceMovesListCell with the data of possible moves
	for (i = 0; i < BOARD_SIZE; i++)
	{
		//if row is even: the col we play on are start from 1
		if (i % 2 == 0)
			colStartFrom = 1;


		for (j = colStartFrom; j < BOARD_SIZE; j += 2)
		{
			if (board[i][j] == player)
			{
				currPos = createCheckersPos(i, j); //create current player position
				moves_Tree = FindSingleSourceMoves(board, currPos); //makes SingleSourceMovesTree
				SingleSourceMovesList *singleList = FindSingleSourceOptimalMove(moves_Tree);//makes SingleSourceMovesList
				MultipleSourceMovesListCell* currMultiCell = createMultipleSourceMovesListCell(singleList, NULL);
				insertMultiNodeToTail(lst, currMultiCell); //insert MultipleSourceMovesListCell to end of MultipleSourceMovesList
				freeTree(*moves_Tree);
			}
		}
		colStartFrom = 0;
	}
	return lst;
}

MultipleSourceMovesList makeEmptyMultiList()
{
	MultipleSourceMovesList ls;
	ls.head = ls.tail = NULL;
	return ls;
}

//function creates MultipleSourceMovesListCell from given SingleSourceMovesList and pointer to next MultipleSourceMovesListCell
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* list, MultipleSourceMovesListCell *next)
{
	//memory allocation for new MultipleSourceMovesListCell
	MultipleSourceMovesListCell* newCell = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkMemory(newCell, __LINE__);

	//memory allocation for MultipleSourceMovesListCell's SingleSourceMovesList data
	newCell->single_source_moves_list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkMemory(newCell->single_source_moves_list, __LINE__);

	newCell->single_source_moves_list = list;
	newCell->next = next;

	return newCell;
}

//function insert MultipleSourceMovesListCell to  end of MultipleSourceMovesList
void insertMultiNodeToTail(MultipleSourceMovesList *ls, MultipleSourceMovesListCell *cell)
{
	//if MultipleSourceMovesList is empty
	if (ls->head == NULL && ls->tail == NULL)
		ls->head = ls->tail = cell;

	else
	{
		ls->tail->next = cell; // point new node at the end of list
		ls->tail = cell; // update list's tail
	}
}

/*test: function prints MultipleSourceMovesList
void printMultiList(MultipleSourceMovesList lst)
{
	MultipleSourceMovesListCell *curr = lst.head;
	while (curr != NULL)
	{
		SingleSourceMovesList lst = *(curr->single_source_moves_list);
		printList(lst);
		printf("\n");
		curr = curr->next;
	}
}*/