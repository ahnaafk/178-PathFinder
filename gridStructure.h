#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 10 

//cellData indices. 
#define OPEN 0
#define CONSTRUCTION 1
#define PASSENGER 2
#define DESTINATION 3
#define FALSE 0
#define TRUE 1
typedef struct cell
{
    int coordinates[2];
    int cellData[4];
    //one-hot encoded array where 0 is false, and 1 is true. 
    //[0]: 1 if open, 0 if not.
    //[1]: 1 if construction, 0 if not.
    //[2]: 1 if passenger, 0 if not. 
    //[3]: 1 if destination, 0 if not. 
    struct cell* passenger;
    struct cell* destination;
    struct cell* parent;
    int f_cost;
    int g_cost;
    int h_cost;
} Cell;



void generateRandomIndex(int* array, Cell* grid[GRID_SIZE][GRID_SIZE]);

void createGrid(Cell* grid[GRID_SIZE][GRID_SIZE]);

//helper debug functions
void printGrid(Cell *grid[GRID_SIZE][GRID_SIZE]);

void printCell(Cell *grid[GRID_SIZE][GRID_SIZE]);

//TODO: Check for edge-cases where a destination is boxed in. 
int createConstruction(Cell* grid[GRID_SIZE][GRID_SIZE]);

Cell* createPassenger(Cell* grid[GRID_SIZE][GRID_SIZE]);

Cell* createDestination(Cell* grid[GRID_SIZE][GRID_SIZE]);

//TODO: Create a passenger pickup function which frees the pointer to the passenger.
//TODO: Create a clear destination function which frees the pointer to the destination