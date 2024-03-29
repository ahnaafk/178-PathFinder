#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pathFinder.h"

void printGrid(Cell *grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j]->cellData[OPEN] == TRUE)
                printf("0");
            if (grid[i][j]->cellData[CONSTRUCTION] == TRUE)
                printf("1");
            if (grid[i][j]->cellData[PASSENGER] == TRUE)
                printf("p");
            if (grid[i][j]->cellData[DESTINATION] == TRUE)
                printf("d");
        }
        printf("\n");
    }
}

void printCell(Cell *grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            Cell *current = grid[i][j];
            printf("cellData: [%d,%d,%d,%d] \n", current->cellData[0], current->cellData[1], current->cellData[2], current->cellData[3]);
        }
    }
}

int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            Cell *temp = malloc(sizeof(Cell *));
            grid[i][j] = temp;
        }
    }
    createGrid(grid);
    printGrid(grid);
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