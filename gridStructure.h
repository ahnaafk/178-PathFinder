#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

#define GRID_SIZE 10

// cellData indices.
enum CellData {
    OPEN, CONSTRUCTION, PASSENGER, DESTINATION, BUS
};

#define FALSE 0
#define TRUE 1

void generateRandomIndex(int *array, Cell *grid[GRID_SIZE][GRID_SIZE]);

void createGrid(Cell *grid[GRID_SIZE][GRID_SIZE], LinkedList *targetList);

// helper debug functions
void printGrid(Cell *grid[GRID_SIZE][GRID_SIZE]);

void printCell(Cell *grid[GRID_SIZE][GRID_SIZE]);

// TODO: Check for edge-cases where a destination is boxed in.
int createConstruction(Cell *grid[GRID_SIZE][GRID_SIZE]);

Cell *createPassenger(Cell *grid[GRID_SIZE][GRID_SIZE]);

Cell *createDestination(Cell *grid[GRID_SIZE][GRID_SIZE]);

int neighbourChecker(Cell *grid[GRID_SIZE][GRID_SIZE],int idx[2]);

int isValid(Cell *grid[GRID_SIZE][GRID_SIZE], int x, int y);

// TODO: Create a passenger pickup function which frees the pointer to the passenger.
// TODO: Create a clear destination function which frees the pointer to the destination