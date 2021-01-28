#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  BOARD_SIZE 8


//defining players
#define  B_CELL 'B'
#define  T_CELL 'T'

#define  EMPTY_CELL 0
#define  LEFT 0
#define  RIGHT 1

//flag - moves 
#define  NOMOVE 0
#define  SINGLEMOVE 1
#define	 EAT 2


typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

//----------------------------Tree stuctures--------------------------------//

typedef struct _checkersPos {
	char row;
	char col;
}checkersPos;

typedef struct _SingleSourceMovesTreeNode {
	struct _SingleSourceMovesTreeNode *next_move[2];
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode *source;
} SingleSourceMovesTree;

//------------------------Single List stuctures-----------------------------//

typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
} SingleSourceMovesListCell;

typedef struct _SingleSourceMoveList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;

} SingleSourceMovesList;

//------------------------Multi List stuctures-----------------------------//

typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList *single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
} MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
} MultipleSourceMovesList;



//------------------------Function Declarations----------------------------//

void checkMemory(void* value, int line);
checkersPos* createCheckersPos(int row, int col);
void printBoard(Board board);
void resetBoardToStartPosition(Board board);
void FindMaxCaptures(SingleSourceMovesTreeNode *Tnode, int *max);
void StoreBoard(Board board, char *filename);
void LoadBoard(char *filename, Board board);
void PlayGame(Board board, Player starting_player);

//----------------------------Tree Function-------------------------------//

SingleSourceMovesTreeNode* createMovesTreeNode(Board board, checkersPos *newPos, unsigned short captures, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right);
SingleSourceMovesTree  *FindSingleSourceMoves(Board board, checkersPos *src);
SingleSourceMovesTreeNode *FindSingleSourceMovesHelper(Board board, checkersPos *src, int flag, unsigned short captures, Player currPlayer, Player oppPlayer, int dir);
void printTree(SingleSourceMovesTreeNode *root);

//--------------------------List Function--------------------------------//

void insertNodeToHead(SingleSourceMovesList *ls, SingleSourceMovesListCell *newHead);
int isEmpty(SingleSourceMovesList lst);
void printList(SingleSourceMovesList lst);
void makeSingleList(SingleSourceMovesList *lst, SingleSourceMovesTreeNode *Tnode, int max_captures, int *flag);

SingleSourceMovesListCell* createSingleSourceMoveListCell(SingleSourceMovesTreeNode* Tnode, SingleSourceMovesListCell *next);
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);
SingleSourceMovesList makeEmptyList();


MultipleSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player);
MultipleSourceMovesList makeEmptyMultiList();
void insertMultiNodeToTail(MultipleSourceMovesList *ls, MultipleSourceMovesListCell *cell);
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* list, MultipleSourceMovesListCell *next);

void Turn(Board board, Player player);
MultipleSourceMovesListCell* FindMaxMultiCell(MultipleSourceMovesList lst, int *max);
void printMultiList(MultipleSourceMovesList lst);


int gameOver(Board board);


//-----------------Free Memory Allocation Functions--------------------//

void freeTree(SingleSourceMovesTree t);
void freeTreeRec(SingleSourceMovesTreeNode* root);
void freeSingleSourceMovesList(SingleSourceMovesList *lst);
void freeMultipleSourceMovesList(MultipleSourceMovesList *lst);

