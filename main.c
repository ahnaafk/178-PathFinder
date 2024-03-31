#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pathFinder.h"


int main()
{
    srand(time(NULL));

    Cell *grid[GRID_SIZE][GRID_SIZE];


    //Creates List of Lists
    LinkedList* lists [5];
    LinkedList* passOnBus =createLinkedList();
    lists [0]=passOnBus;
    LinkedList* idlePass =createLinkedList();
    lists [1]=idlePass;
    LinkedList* allDest =createLinkedList();
    lists [2]= allDest;
    LinkedList* idleAndPassOnBus =createLinkedList();
    lists [3]= idleAndPassOnBus;
    LinkedList* pathToTrgt =createLinkedList();
    lists [4]= pathToTrgt;


    createGrid(grid);
    printGrid(grid);

    Heap* closed_list = createHeap(); 

        for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            
            free(grid[i][j]);
        }
    }

    return 0;
}