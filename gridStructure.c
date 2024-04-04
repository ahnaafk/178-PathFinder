#include <stdio.h>
#include "gridStructure.h"

#define CONSTRUCTION_POINTS 30
#define PASSENGER_COUNT 5
#define VERBOSE 0
#define RANDOM 0

enum EXIT
{
    EXIT_OK,
    EXIT_ERR
};

void generateRandomIndex(int *array, Cell *grid[GRID_SIZE][GRID_SIZE])
{
    // method to generate random integers between 1 and N that i found online.
    int x;
    int y;

    // If the indexed cell is NOT an open space, then we cannot turn it into something else.
    do
    {
        x = rand() % (GRID_SIZE);
        y = rand() % (GRID_SIZE);
    } while ((x == 0 && y == 0) || (grid[x][y] && grid[x][y]->cellData[OPEN] == FALSE));

    array[0] = x;
    array[1] = y;
}

void createGrid(Cell *grid[GRID_SIZE][GRID_SIZE], LinkedList *masterList[5])
{
    // initalize each part of the grid to an open space by default

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            // Allocate memory for a new Cell
            grid[i][j] = malloc(sizeof(Cell));
            if (grid[i][j] == NULL)
            {
                // Handle memory allocation failure
                fprintf(stderr, "Memory allocation failed for grid[%d][%d]\n", i, j);
                exit(EXIT_ERR);
            }

            grid[i][j]->coordinates[0] = i;
            grid[i][j]->coordinates[1] = j;
            grid[i][j]->cellData[OPEN] = 1;
            grid[i][j]->cellData[CONSTRUCTION] = 0;
            grid[i][j]->cellData[PASSENGER] = 0;
            grid[i][j]->cellData[DESTINATION] = 0;
        }
    }

    // randomly create construction points along grid
    for (int i = 0; i < CONSTRUCTION_POINTS; i++)
    {
        createConstruction(grid, i);
    }

    // // create random passenger destination pairs.
    for (int i = 0; i < PASSENGER_COUNT; i++)
    {
        Cell *pass = createPassenger(grid);
        addNode(masterList[IDLEPASS], pass);

        // each passenger on the board is also a valid target.
        addNode(masterList[TARGETLIST], pass);
        Cell *dest = createDestination(grid);

        // point each pair to each other so that the algorithm always knows the where corresponding element in the pair is.
        pass->destination = dest;
        dest->passenger = pass;

        // set verbose to true when debugging.
        if (VERBOSE == TRUE)
        {
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
int createConstruction(Cell *grid[GRID_SIZE][GRID_SIZE], int i)
{

    // random ints used to index grid
    int idx[2];
    int rx;
    int ry;
    // Makes sure construction point are not too clustered
    do
    {
        generateRandomIndex(idx, grid);
        rx = idx[0];
        ry = idx[1];
    } while (neighbourChecker(grid, idx));

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[CONSTRUCTION] = TRUE;

    return EXIT_OK;
}

// Create randomized passenger
Cell *createPassenger(Cell *grid[GRID_SIZE][GRID_SIZE])
{
    int idx[2];
    int rx = idx[0];
    int ry = idx[1];

    if (RANDOM == TRUE) // if we are testing, use the random toolset for ease.
    {
        do
        {
            generateRandomIndex(idx, grid);
            rx = idx[0];
            ry = idx[1];

        } while ((idx[0] == 0 && idx[1] == 0) || (grid[idx[0]][idx[1]]->cellData[CONSTRUCTION] == TRUE));
    }
    else // for presentation set random to 0 so we can take user input.
    {
        do
        {
            printf("Please input the coordinates of passenger: ");
            scanf("%d %d", rx, ry);

            // if the passenger is set at 0,0 or the cell is already a construction point, reprompt.
            if ((rx == 0 && ry == 0) || (grid[rx][ry]->cellData[CONSTRUCTION] == TRUE))
                printf("Invalid input \n");

        } while ((rx == 0 && ry == 0) || (grid[rx][ry]->cellData[CONSTRUCTION] == TRUE));
    }

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[PASSENGER] = TRUE;

    return grid[rx][ry];
}

// Create randomized destination
Cell *createDestination(Cell *grid[GRID_SIZE][GRID_SIZE])
{
    int idx[2];
    int rx = idx[0];
    int ry = idx[1];

    if (RANDOM == TRUE) // if we are testing, use the random toolset for ease.
    {
        do
        {
            generateRandomIndex(idx, grid);
            rx = idx[0];
            ry = idx[1];

        } while ((idx[0] == 0 && idx[1] == 0) || (grid[idx[0]][idx[1]]->cellData[CONSTRUCTION] == TRUE));
    }
    else // for presentation set random to 0 so we can take user input.
    {
        do
        {
            printf("Please input the coordinates of destination: ");
            scanf("%d %d", rx, ry);

            // if the destination is set at 0,0 or the cell is already a construction point, reprompt.
            if ((rx == 0 && ry == 0) || (grid[rx][ry]->cellData[CONSTRUCTION] == TRUE))
                printf("Invalid input \n");

        } while ((rx == 0 && ry == 0) || (grid[rx][ry]->cellData[CONSTRUCTION] == TRUE));
    }

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[DESTINATION] = TRUE;

    return grid[rx][ry];
}

void printGrid(Cell *grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = GRID_SIZE; i > 0; i--)
    {
        for (int j = GRID_SIZE; j > 0; j--)
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
            printf("cellData: [%d,%d,%d,%d] \n", current->cellData[0], current->cellData[1], current->cellData[2],
                   current->cellData[3]);
        }
    }
}
int neighbourChecker(Cell *grid[GRID_SIZE][GRID_SIZE], int idx[2])
{
    int count = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;
            int checkX = idx[0] + x;
            int checkY = idx[1] + y;

            // if the new x and y are valid, then check the neighbour at that location
            if (checkX >= 0 && checkX < GRID_SIZE && checkY >= 0 && checkY < GRID_SIZE)
            {
                Cell *neighbour = grid[checkX][checkY];
                // if the neighbour is construction, or is in the closed list, then skip iteration
                if (neighbour->cellData[CONSTRUCTION] == TRUE)
                {
                    count++;
                }
            }
        }
    }
    if (count > 5)
    {
        return TRUE;
    }
    else if (count < 5)
    {
        return FALSE;
    }
}