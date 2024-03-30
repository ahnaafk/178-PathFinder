#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pathFinder.h"


int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];
    
    createGrid(grid);
    // printGrid(grid);
    printCell(grid);

        for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            
            free(grid[i][j]);
        }
    }

    return 0;
}