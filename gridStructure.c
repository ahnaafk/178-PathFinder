#include <stdio.h>
#include "gridStructure.h"

#define CONSTRUCTION_POINTS 30
#define PASSENGER_COUNT 5 // used for random passenger-destination creation
#define VERBOSE 0         // for debugging
#define RANDOM 0          // set to 1 if you want random passenger-destination pairs.

enum EXIT
{
    EXIT_OK,
    EXIT_ERR
};

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
            grid[i][j]->cellData[CONSTRUCTION] = FALSE;
            grid[i][j]->cellData[PASSENGER] = FALSE;
            grid[i][j]->cellData[DESTINATION] = FALSE;
            if (i == 0 && j == 0)
            {
                grid[i][j]->cellData[BUS] = TRUE;
                grid[i][j]->cellData[OPEN] = FALSE;
            }
            else
            {
                grid[i][j]->cellData[BUS] = FALSE;
            }
        }
    }

    // randomly create construction points along grid
    for (int i = 0; i < CONSTRUCTION_POINTS; i++)
    {
        createConstruction(grid);
    }

    // create random passenger destination pairs.
    if (RANDOM == TRUE)
    {
        for (int i = 0; i < PASSENGER_COUNT; i++)
        {
        Cell *pass = createPassenger(grid);

        // each passenger on the grid is a valid target.
        addNode(masterList[TARGETLIST], pass);

        Cell *dest = createDestination(grid);

        // point each pair to each other so that the algorithm always knows the where corresponding element in the pair is.
        pass->destination = dest;
        dest->passenger = pass;
        }
    }
    else
    {
        int input = 0;
        int go_next = FALSE;
        do
        {
            printf("There are/is currently %d passenger-destination pair(s) \n", masterList[TARGETLIST]->count);
            printf("Please input 1 to create a passenger-destination pair, or 2 to continue to pathfinding: ");
            scanf("%d", &input);

            if (input == 1)
            {
                Cell *pass = createPassenger(grid);

                // each passenger on the grid is a valid target.
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
            else if (input == 2)
            {
                // check first that the lists aren't empty before exiting.
                if (masterList[TARGETLIST]->count == 0)
                {
                    printf("Oops! You silly billy, you didn't input a passenger-destination pair. Please do so now. \n");
                }
                else
                {
                    // if lists have something in them, then continue.
                    go_next = TRUE;
                }
            }
            else
            {
                printf("Oops! You silly billy, that's an invalid input \n");
            }

        } while (go_next == FALSE);
    }

    return;
}

// Randomly generate a construction point within the grid.
int createConstruction(Cell *grid[GRID_SIZE][GRID_SIZE])
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

        } while (!isValid(grid, rx, ry));
    }
    else // for presentation set random to 0 so we can take user input.
    {
        do
        {
            printf("Please input the coordinates of passenger: ");
            scanf("%d %d", &rx, &ry);

            // if the cell is not valid, reprompt
            if (!isValid(grid, rx, ry))
            {
                printf("Invalid input \n");
                // printf("Please input the coordinates of passenger: ");
                // scanf("%d %d", &rx, &ry);
            }

        } while (!isValid(grid, rx, ry));
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

        } while (!isValid(grid, rx, ry));
    }
    else // for presentation set random to 0 so we can take user input.
    {
        do
        {
            printf("Please input the coordinates of destination: ");
            scanf("%d %d", &rx, &ry);

            // if the destination is set at 0,0 or the cell is already a construction point, reprompt.
            if (!isValid(grid, rx, ry))
            {
                printf("Invalid input \n");
                continue;
            }

        } while (!isValid(grid, rx, ry));
    }

    grid[rx][ry]->cellData[OPEN] = FALSE;
    grid[rx][ry]->cellData[DESTINATION] = TRUE;

    return grid[rx][ry];
}

void printGrid(Cell *grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = GRID_SIZE - 1; i >= 0; i--)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j]->cellData[OPEN] == TRUE)
                printf("0");
            if (grid[i][j]->cellData[CONSTRUCTION] == TRUE)
                printf("1");
            if (grid[i][j]->cellData[PASSENGER] == TRUE)
                printf("P");
            if (grid[i][j]->cellData[DESTINATION] == TRUE)
                printf("D");
            if (grid[i][j]->cellData[BUS] == TRUE)
                printf("B");
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

int isValid(Cell *grid[GRID_SIZE][GRID_SIZE], int x, int y)
{

    if (x == 0 && y == 0)
    {
        return FALSE;
    }
    else if (x < 0 || x > 9)
    {
        return FALSE;
    }
    else if (y < 0 || y > 9)
    {
        return FALSE;
    }
    else if (grid[x][y]->cellData[OPEN] == FALSE)
    {
        return FALSE;
    }

    return TRUE;
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
                // if the neighbour is construction, then increase the count.
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
    return FALSE;
}

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