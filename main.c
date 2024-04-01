#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pathFinder.h"

int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];

    // Creates List of Lists
    LinkedList *masterList[4];
    LinkedList *passOnBus = createLinkedList();
    masterList[PASSONBUS] = passOnBus;
    LinkedList *idlePass = createLinkedList();
    masterList[IDLEPASS] = idlePass;
    LinkedList *allDest = createLinkedList();
    masterList[ALLDEST] = allDest;
    LinkedList *targetList = createLinkedList();
    masterList[TARGETLIST] = targetList;
    // Creates List of paths
    LinkedList *listOfPaths[35];

    createGrid(grid, masterList);
    printGrid(grid);

    astar(grid, grid[0][0], masterList, listOfPaths);

    LinkedList* newList = createLinkedList(); 
    addNode(newList, grid[0][0]);
    addNode(newList, grid[1][1]);
    addNode(newList, grid[2][2]);
    addNode(newList, grid[3][3]);
    addNode(newList, grid[4][4]);

    displayList(listOfPaths[0]);
    displayList(listOfPaths[1]);

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {

            free(grid[i][j]);
        }
    }
    return 0;
}