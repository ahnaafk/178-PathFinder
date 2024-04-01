#include <stdio.h>
#include "gridStructure.h"

#define CONSTRUCTION_POINTS 30
#define PASSENGER_COUNT 5
#define VERBOSE 0

int constructionPoints[CONSTRUCTION_POINTS][2];

enum EXIT {
    EXIT_OK,
    EXIT_ERR
};

void generateRandomIndex(int *array, Cell *grid[GRID_SIZE][GRID_SIZE]) {
    // method to generate random integers between 1 and N that i found online.
    // random ints used to index grid
    int x = rand() % (GRID_SIZE);
    int y = rand() % (GRID_SIZE);

    // If the indexed cell is NOT an open space, then we cannot turn it into something else.
    while (grid[x][y]->cellData[OPEN] == FALSE) {
        x = rand() % (GRID_SIZE);
        y = rand() % (GRID_SIZE);
    }

    array[0] = x;
    array[1] = y;
}

void createGrid(Cell *grid[GRID_SIZE][GRID_SIZE], LinkedList *masterList[5]) {
    // initalize each part of the grid to an open space by default
    // Cell grid[GRID_SIZE][GRID_SIZE];
    printf("-----at initalization\n");

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            // Allocate memory for a new Cell
            grid[i][j] = malloc(sizeof(Cell));
            if (grid[i][j] == NULL) {
                // Handle memory allocation failure
                fprintf(stderr, "Memory allocation failed for grid[%d][%d]\n", i, j);
                exit(EXIT_ERR);
            }

            // printf("checkpoint 0, i: %d, j: %d \n", i, j);

            grid[i][j]->coordinates[0] = i;
            grid[i][j]->coordinates[1] = j;
            grid[i][j]->cellData[OPEN] = 1;
            grid[i][j]->cellData[CONSTRUCTION] = 0;
            grid[i][j]->cellData[PASSENGER] = 0;
            grid[i][j]->cellData[DESTINATION] = 0;
            // printf("cellData: [%d,%d,%d,%d] \n", grid[i][j]->cellData[0], grid[i][j]->cellData[1], grid[i][j]->cellData[2], grid[i][j]->cellData[3]);
            // printf("coordinates of cell[%d][%d]: [%d][%d] \n", i,j, grid[i][j] -> coordinates[0], grid[i][j] -> coordinates[1]);
        }
    }


    // randomly create construction points along grid
    for (int i = 0; i < CONSTRUCTION_POINTS; i++) {
        //figure out how to avoid the boxed in edge-case
        createConstruction(grid, i);
        
    }

    // // create random passenger destination pairs.
    // Cell* destArr[PASSENGER_COUNT];
    // Cell* passArr[PASSENGER_COUNT];
    for (int i = 0; i < PASSENGER_COUNT; i++) {
        //TODO for ETHAN: each time we create a passenger, also must add the pair to a linked list. Done
        Cell *pass = createPassenger(grid);
        addNode(masterList[1], pass);
        Cell *dest = createDestination(grid);
        addNode(masterList[2], dest);

        // //populate the array with the pairs for ease of accessk
        // passArr[i] = pass;
        // destArr[i] = dest;

        // point each pair to each other so that the algorithm always knows the where corresponding element in the pair is.
        pass->destination = dest;
        dest->passenger = pass;

        // set verbose to true when debugging.
        if (VERBOSE == TRUE) {
            printf("destination: [%d][%d] \n", dest->coordinates[0], dest->coordinates[1]);
            printf("passenger: [%d][%d] \n", pass->coordinates[0], pass->coordinates[1]);
            printf("destination referencing the passenger: [%d][%d] \n", dest->passenger->coordinates[0],
                   dest->passenger->coordinates[1]);
            printf("passenger referencing the destination: [%d][%d] \n", pass->destination->coordinates[0],
                   pass->destination->coordinates[1]);
        }
    }

    return;
}

// Randomly generate a construction point within the grid.
int createConstruction(Cell *grid[GRID_SIZE][GRID_SIZE], int i) {
    // random ints used to index grid
    int idx[2];
    generateRandomIndex(idx, grid);
    int rx = idx[0];
    int ry = idx[1];

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[CONSTRUCTION] = TRUE;

    constructionPoints[i][0] = rx;
    constructionPoints[i][1] = ry;

    return EXIT_OK;
}

// Create randomized passenger
Cell *createPassenger(Cell *grid[GRID_SIZE][GRID_SIZE]) {
    int idx[2];
    generateRandomIndex(idx, grid);
    int rx = idx[0];
    int ry = idx[1];

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[PASSENGER] = TRUE;

    return grid[rx][ry];
}

// Create randomized destination
Cell *createDestination(Cell *grid[GRID_SIZE][GRID_SIZE]) {
    int idx[2];
    generateRandomIndex(idx, grid);
    int rx = idx[0];
    int ry = idx[1];

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[DESTINATION] = TRUE;

    return grid[rx][ry];
}

void printGrid(Cell *grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
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

void printCell(Cell *grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Cell *current = grid[i][j];
            printf("cellData: [%d,%d,%d,%d] \n", current->cellData[0], current->cellData[1], current->cellData[2],
                   current->cellData[3]);
        }
    }
}
