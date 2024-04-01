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
    LinkedList *changeLog = createLinkedList();
    masterList[CHANGELOG] = changeLog;
    LinkedList *targetList = createLinkedList();
    masterList[TARGETLIST] = targetList;
    // Creates List of paths
    LinkedList *listOfPaths[35];

    createGrid(grid, masterList);
    printGrid(grid);
    LinkedList *routeInfo = createLinkedList();

    astar(grid, grid[0][0], masterList, listOfPaths);

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {

            free(grid[i][j]);
        }
    }
    return 0;
}