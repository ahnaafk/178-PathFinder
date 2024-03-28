#include <stdio.h>
#include <stdlib.h>
#include "gridStructure.h"
#include "pathFinder.h"
#include <time.h>

void printGrid(Cell grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j].cellData[OPEN] == TRUE)
                printf("0");
            if (grid[i][j].cellData[CONSTRUCTION] == TRUE)
                printf("1");
            if (grid[i][j].cellData[PASSENGER] == TRUE)
                printf("p");
            if (grid[i][j].cellData[DESTINATION] == TRUE)
                printf("d");
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    Cell grid[GRID_SIZE][GRID_SIZE];
    createGrid(grid);
    printGrid(grid);

    return 0;
}