#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Cell *findMinTarget(Cell *start, LinkedList *targetList);

void astar(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *start, LinkedList *masterList[4], LinkedList *listOfPaths[35]);

Cell *pathFinder(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *startNode, Cell *targetNode, LinkedList *[4], LinkedList *listOfPaths[35]);

void retracePath(Cell *startCell, Cell *endCell, LinkedList *masterList[4], LinkedList *listOfPaths[35]);

void reverseList(LinkedList *list);

int getDistance(Cell *A, Cell *B);

int gCost(Cell *startNode, Cell *currentNode);

int hCost(Cell *targetNode, Cell *currentNode);

int fCost(Cell *startNode, Cell *targetNode, Cell *currentNode);

int inOpen(Heap *h, Cell *node);

int inList(LinkedList *list, Cell *node);
