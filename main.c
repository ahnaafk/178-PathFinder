#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pathFinder.h"


int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];


    //Creates List of Lists
    LinkedList* masterList [5];
    LinkedList* passOnBus =createLinkedList();
    masterList [0]=passOnBus;
    LinkedList* idlePass =createLinkedList();
    masterList [1]=idlePass;
    LinkedList* allDest =createLinkedList();
    masterList [2]= allDest;
    LinkedList* idleAndDestOnBus =createLinkedList();
    masterList [3]= idleAndDestOnBus;
    LinkedList* pathToTrgt =createLinkedList();
    masterList [4]= pathToTrgt;


    createGrid(grid,masterList);
    printGrid(grid);


        for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            
            free(grid[i][j]);
        }
    }

    return 0;
}