#include <stdio.h>
#include <stdlib.h>
typedef struct cell
{
    int coordinates[2]; 
    int cellData[4]; //one-hot encoded array where 0 is false, and 1 is true. 
    pCell *passenger;
    pCell *destination;
} Cell, *pCell;

Cell grid[10][10];

int move(int direction[2], int coordinates[2]);