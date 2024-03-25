#include <stdio.h>
#include "gridStructure.h"
#define CONSTRUCTION_POINTS 30
#define PASSENGER_COUNT 5
#define VERBOSE 0

enum EXIT
{
  EXIT_OK,
  EXIT_ERR
};

void generateRandomIndex(int *array)
{
  // method to generate random integers between 1 and N that i found online.
  // random ints used to index grid
  int x = rand() % (GRID_SIZE);
  int y = rand() % (GRID_SIZE);

  // If the indexed cell is NOT an open space, then we cannot turn it into something else.
  while (grid[x][y].cellData[OPEN] == FALSE)
  {
    x = rand() % (GRID_SIZE);
    y = rand() % (GRID_SIZE);
  }

  array[0] = x;
  array[1] = y;
}

int createGrid()
{
  // initalize each part of the grid to an open space by default
  int count = 0;
  for (int i = 0; i < GRID_SIZE; i++)
  {
    for (int j = 0; j < GRID_SIZE; j++)
    {
      grid[i][j].coordinates[0] = i;
      grid[i][j].coordinates[1] = j;
      grid[i][j].cellData[OPEN] = 1;

      // randomly create construction points along grid
      if (count < CONSTRUCTION_POINTS)
        createConstruction();
      count++;
    }
  }

  // create random passenger destination pairs.
  for (int i = 0; i < PASSENGER_COUNT; i++)
  {
    Cell *pass = createPassenger();
    Cell *dest = createDestination();

    //point each pair to each other so that the algorithm always knows the where corresponding element in the pair is. 
    pass -> destination = dest;
    dest -> passenger = pass;

    //set verbose to true when debugging.
    if (VERBOSE == TRUE) {
    printf("destination: [%d][%d] \n", dest->coordinates[0], dest->coordinates[1]);
    printf("passenger: [%d][%d] \n", pass->coordinates[0], pass->coordinates[1]);
    printf("destination referencing the passenger: [%d][%d] \n", dest-> passenger->coordinates[0], dest-> passenger->coordinates[1]);
    printf("passenger referencing the destination: [%d][%d] \n", pass-> destination->coordinates[0], pass-> destination->coordinates[1]);

    }
  }
  return EXIT_OK;
}

// Randomly generate a construction point within the grid.
int createConstruction()
{
  // random ints used to index grid
  int idx[2];
  generateRandomIndex(idx);
  int rx = idx[0];
  int ry = idx[1];

  grid[rx][ry].cellData[OPEN] = FALSE;
  grid[rx][ry].cellData[CONSTRUCTION] = TRUE;

  return EXIT_OK;
}

// Create randomized passenger
Cell *createPassenger()
{
  int idx[2];
  generateRandomIndex(idx);
  int rx = idx[0];
  int ry = idx[1];
  
  Cell *pass = malloc(sizeof(Cell *));
  pass = &grid[rx][ry];
  
  pass->cellData[OPEN] = FALSE;
  pass->cellData[PASSENGER] = TRUE;

  return pass;
}

// Create randomized destination
Cell *createDestination()
{
  int idx[2];
  generateRandomIndex(idx);
  int rx = idx[0];
  int ry = idx[1];

  Cell *dest = malloc(sizeof(Cell *));
  dest = &grid[rx][ry];

  dest->cellData[OPEN] = FALSE;
  dest->cellData[DESTINATION] = TRUE;

  return dest;
}