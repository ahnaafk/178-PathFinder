#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pathFinder.h"

int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];

    // Creates List of Lists
    LinkedList *masterList[2];

    masterList[BUSLIST] = createLinkedList();
    masterList[TARGETLIST] = createLinkedList();

    // Creates List of all successful paths taken. maximum 35 paths to be taken. since there are only 70 free spots on the grid. 
    LinkedList *pathList[34];

    createGrid(grid, masterList);
    printf("Initial grid: \n");
    printGrid(grid);

    astar(grid, grid[0][0], masterList, pathList);

    printf("No more passengers to drop off! We are done here. \n");
    

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {

            free(grid[i][j]);
        }
    }

    free(masterList[TARGETLIST]);
    free(masterList[BUSLIST]);

    return 0;
}