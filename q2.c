#include "general.h"


//-----------------------------------q2----------------------------------//

//function finds the best route to do and return a SingleSourceMovesList
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
	//memory allocation for SingleSourceMovesList
	SingleSourceMovesList *lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkMemory(lst, __LINE__);
	*lst = makeEmptyList();

	int flag = 0, max_captures = 0;

	//finding which route is "better": the max eating of oppPlayer
	FindMaxCaptures(moves_tree->source, &max_captures);

	//in case there are no captures we'll create list with one node of the specific cell
	if (max_captures == 0)
	{
		SingleSourceMovesListCell *newCell, *newCellSon;

		//if there is no cell the current player in current position can move
		if (moves_tree->source->next_move[0] == NULL && moves_tree->source->next_move[1] == NULL)
			newCellSon = NULL;

		//if there is only one cell to move
		else if (moves_tree->source->next_move[0] == NULL)
			newCellSon = createSingleSourceMoveListCell(moves_tree->source->next_move[1], NULL);
		else if (moves_tree->source->next_move[1] == NULL)
			newCellSon = createSingleSourceMoveListCell(moves_tree->source->next_move[0], NULL);

		//else: if the player can choose between 2 cells: default is to go to the left
		else
			newCellSon = createSingleSourceMoveListCell(moves_tree->source->next_move[0], NULL);


		newCell = createSingleSourceMoveListCell(moves_tree->source, newCellSon);

		//updating list
		if (newCellSon == NULL)
			lst->head = lst->tail = newCell;
		else
		{
			lst->head = newCell;
			lst->tail = newCellSon;
		}

	}

	//in case the player can do a move which it'll eat the opposite Player
	else
		makeSingleList(lst, moves_tree->source, max_captures, &flag);

	return lst;
}

//function finds the max-capture in tree
void FindMaxCaptures(SingleSourceMovesTreeNode *Tnode, int *max)
{
	if (!Tnode)
		return;
	else if (Tnode->next_move[0] == NULL && Tnode->next_move[1] == NULL) //if leaf
	{
		//if leaf has more captures then max replacing "max" value
		*max = (*max >= (const)Tnode->total_captures_so_far ? *max : Tnode->total_captures_so_far);
		return;
	}

	FindMaxCaptures(Tnode->next_move[0], max); //Left node
	FindMaxCaptures(Tnode->next_move[1], max); //Right node
}

//function makes SingleSourceMovesList
void makeSingleList(SingleSourceMovesList *lst, SingleSourceMovesTreeNode *Tnode, int max_captures, int *flag)
{
	if (!Tnode)
		return;
	//if current leaf has max-captuers we found - we buliding the list
	else if (Tnode->next_move[0] == NULL && Tnode->next_move[1] == NULL && Tnode->total_captures_so_far == max_captures)
	{
		SingleSourceMovesListCell* newCell = createSingleSourceMoveListCell(Tnode, NULL);
		insertNodeToHead(lst, newCell);
		*flag = 1;
		return;
	}

	makeSingleList(lst, Tnode->next_move[0], max_captures, flag);
	makeSingleList(lst, Tnode->next_move[1], max_captures, flag);

	//if the tnode is in the route of max-capture: adding to list
	if (*flag == 1)
	{
		SingleSourceMovesListCell* newCell = createSingleSourceMoveListCell(Tnode, NULL);
		insertNodeToHead(lst, newCell);
	}
	return;
}


//function return 0 if given SingleSourceMovesList is not empty 
int isEmpty(SingleSourceMovesList lst)
{
	return (lst.head == NULL);
}

//function inserts SingleSourceMovesListCell into head of given SingleSourceMovesList 
void insertNodeToHead(SingleSourceMovesList *ls, SingleSourceMovesListCell *newHead)
{
	if (isEmpty(*ls))
		ls->tail = newHead;

	newHead->next = ls->head; // point new node at the start of the list
	ls->head = newHead; // update list's head
}

//function creates SingleSourceMovesListCell from given SingleSourceMovesTreeNode
SingleSourceMovesListCell* createSingleSourceMoveListCell(SingleSourceMovesTreeNode* Tnode, SingleSourceMovesListCell *next)
{
	//memory allocationfor new SingleSourceMovesListCell
	SingleSourceMovesListCell* newCell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkMemory(newCell, __LINE__);

	newCell->position = createCheckersPos(Tnode->pos->row - '0', Tnode->pos->col - '0');
	newCell->captures = Tnode->total_captures_so_far;
	newCell->next = next;

	return newCell;
}

//function makes empty SingleSourceMovesList
SingleSourceMovesList makeEmptyList()
{
	SingleSourceMovesList ls;
	ls.head = ls.tail = NULL;
	return ls;
}

//function prints SingleSourceMovesList
void printList(SingleSourceMovesList lst)
{
	SingleSourceMovesListCell* curr = lst.head;
	printf("The positions in list are:  ");
	while (curr != NULL)
	{
		printf("[%c][%c] ", 'A' + curr->position->row - '0', 1 + curr->position->col);
		curr = curr->next;
	}
	printf("\n");
}