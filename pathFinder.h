#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Cell* findMinTarget(Cell* start, Cell* passengers[], Cell* destinations[]);

void astar(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *start, Cell *passengers[], Cell *destinations[]);

Cell *pathFinder(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *startNode, Cell *targetNode);

// void retracePath(Cell startNode, Cell endNode);

int getDistance(Cell* A, Cell* B);

int gCost(Cell* startNode, Cell* currentNode);

int hCost(Cell* targetNode, Cell* currentNode);

int fCost(Cell* startNode, Cell* targetNode, Cell* currentNode);

int inClosed(Heap* h, Cell* node);

int inList(LinkedList* list, Cell* node);
