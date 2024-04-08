#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pathFinder.h"

int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];

    // Creates list of all targets
    LinkedList *targetList = createLinkedList();

    // Creates list of all successful paths taken. maximum 35 paths to be taken. since there are only 70 free spots on the grid.
    LinkedList *pathList[34];

    createGrid(grid, targetList);
    printf("Initial grid: \n");
    printGrid(grid);

    int status = pathFinder(grid, grid[0][0], targetList, pathList);

    if (status == EXIT_FAILURE)
    {
        printf("Failed");
    }
    else
    {

        printf("No more passengers to drop off! We are done here. \n");
    }

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {

            free(grid[i][j]);
        }
    }

    free(targetList);

    return 0;
}