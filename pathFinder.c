#include "pathFinder.h"
#include <math.h>
int pathCount = 0; 

// Finds min target from starting cell, finds shortest path from starting
int pathFinder(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *start, LinkedList *masterList[4], LinkedList *pathList[35])
{
    Cell *busCell = start;
    Cell *targetCell;
    // Loop while targets are still available
    while (masterList[TARGETLIST]->head != NULL)
    {
        //Set the current cell where the bus is to an open space since it'll move to its new destination.
        busCell -> cellData[BUS] = FALSE;
        busCell -> cellData[OPEN] = TRUE;

        // Find the next target, which has the minimum h-cost of all the possible targets. 
        targetCell = findMinTarget(busCell, masterList[TARGETLIST]);

        // Finds the path to next target and updates the bus so that it is now at that target cell. 
        busCell = astar(grid, busCell, targetCell, masterList, pathList);
        if (busCell == NULL) return EXIT_FAILURE;

        // Passenger pickup routine:
        if (busCell->cellData[PASSENGER] == 1)
        {
            // Add the passenger's destination to the target list and add the passenger to the buslist
            addNode(masterList[TARGETLIST], busCell->destination);
            addNode(masterList[BUSLIST], busCell);

            // Delete the passenger from the target list.
            // deleteNode(masterList[IDLEPASS], findNode(masterList[IDLEPASS], busCell));
            deleteNode(masterList[TARGETLIST], findNode(masterList[TARGETLIST], busCell));

            //After picking up a passenger, we update the cell to reflect the passenger being picked up and the bus moving to that new cell.
            busCell -> cellData[PASSENGER] = FALSE;
            busCell -> cellData[BUS] = TRUE;
        }
        // Passenger dropoff routine
        else if (busCell->cellData[DESTINATION] == 1)
        {
            // Delete the destination off of the target list and delete the passenger from the bus list .
            deleteNode(masterList[TARGETLIST], findNode(masterList[TARGETLIST], busCell));
            deleteNode(masterList[BUSLIST], findNode(masterList[BUSLIST], busCell));

            //After dropping off a passenger, we update the cell to reflect the passenger being dropped off and the bus moving to that new cell.
            busCell -> cellData[DESTINATION] = FALSE;
            busCell -> cellData[BUS] = TRUE;
        }

        //Update grid routine:
        printf("Path %d: \n", pathCount + 1);
        printGrid(grid);
        displayList(pathList[pathCount]);
        pathCount++;
        printf("\n");
    }
    return EXIT_SUCCESS;
}

Cell *findMinTarget(Cell *start, LinkedList *targetList)
{

    // possible objectives
    // 1. a passenger that we haven't picked up
    // 2. a destination of a passenger that we HAVE picked up.

    Cell *minTarget = NULL;
    int minHCost;
    Node *traverser = targetList->head;
    while (traverser != NULL)
    {
        if (traverser == targetList->head)
        {
            minHCost = hCost(traverser->cell, start);
            minTarget = traverser->cell;
        }
        else
        {
            if (hCost(traverser->cell, start) < minHCost)
            {
                minHCost = hCost(traverser->cell, start);
                minTarget = traverser->cell;
            }
        }
        traverser = traverser->next;
    }
    return (minTarget);
}

// finds a path to a target node, returns the new starting node.
Cell *astar(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *startNode, Cell *targetNode, LinkedList *masterList[4], LinkedList *pathList[35])
{

    // Initialize openSet
    Heap *openSet = createHeap();
    // Initialize closedSet
    LinkedList *closedSet = createLinkedList();

    // Add startNode to open set
    pushHeap(openSet, startNode);

    while (openSet->size > 0)
    {
        // Take smallest f node or if equal take lowest h
        Cell *currentNode = popHeap(openSet);

        // add current node to closed set
        addNode(closedSet, currentNode);

        // if the coordinates match between the current node and the target node, we have a match!
        if (currentNode->coordinates[0] == targetNode->coordinates[0] && currentNode->coordinates[1] == targetNode->coordinates[1])
        {
            retracePath(startNode, currentNode, masterList, pathList);
            return currentNode;
        }

        // get each neighbour of the current node.
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (x == 0 && y == 0)
                    continue;
                int checkX = currentNode->coordinates[0] + x;
                int checkY = currentNode->coordinates[1] + y;

                // if the new x and y are valid, then check the neighbour at that location
                if (checkX >= 0 && checkX < GRID_SIZE && checkY >= 0 && checkY < GRID_SIZE)
                {
                    Cell *neighbour = grid[checkX][checkY];
                    // if the neighbour is construction, or is in the closed list, then skip iteration
                    if (neighbour->cellData[CONSTRUCTION] == TRUE || inList(closedSet, neighbour))
                        continue;

                    // if the new path to neighbour is shorter OR the neighbour is not in the open then...

                    // TODO: verify this logic
                    // TODO create the isOpen function once linked list is created.
                    if (gCost(currentNode, neighbour) < neighbour->g_cost || !inOpen(openSet, neighbour))
                    {
                        neighbour->f_cost = fCost(startNode, targetNode, neighbour);
                        neighbour->g_cost = gCost(startNode, neighbour);
                        neighbour->h_cost = hCost(targetNode, neighbour);
                        neighbour->parent = currentNode;
                        if (!inOpen(openSet, neighbour))
                            pushHeap(openSet, neighbour);
                    }
                }
            }
        }
    }
    free(openSet);
    free(closedSet);
    printf("Null path. Likely boxed in \n");
    return NULL;
}

void retracePath(Cell *startCell, Cell *endCell, LinkedList *masterList[4], LinkedList *pathList[35])
{

    Cell *currentCell = endCell;
    pathList[pathCount] = createLinkedList();

    // Create a templist with all the parents of the nodes. Head -> endNode
    while (currentCell != startCell)
    {
        addNode(pathList[pathCount], currentCell);
        currentCell = currentCell->parent;
    }

    addNode(pathList[pathCount], currentCell);

    // Reverse path now because it's in opposite order.
    reverseList(pathList[pathCount]);
}

void reverseList(LinkedList *list)
{
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

int getDistance(Cell *A, Cell *B)
{
    // implicitly we state that adjacent nodes cost 10 distance while diagonal nodes cost 14 distance
    int xDistance = abs((A->coordinates[0]) - (B->coordinates[0]));
    int yDistance = abs((A->coordinates[1]) - (B->coordinates[1]));

    if (xDistance > yDistance)
    {
        return 14 * yDistance + 10 * (xDistance - yDistance);
    }
    else
    {
        return 14 * xDistance + 10 * (yDistance - xDistance);
    }
}

//--------TODO: fix the naming convention of these functions. ------

// gCost function: How far away from start
int gCost(Cell *startNode, Cell *currentNode)
{
    return getDistance(startNode, currentNode);
}

// hCost function: How close to goal node.
// Using diagonal distance heuristic.
int hCost(Cell *targetNode, Cell *currentNode)
{
    int dx = abs(currentNode->coordinates[0] - targetNode->coordinates[0]);
    int dy = abs(currentNode->coordinates[1] - targetNode->coordinates[1]);
    int D = 10;  // g-cost of an adjacent node
    int D2 = 14; // g-cost of a diagonal node
    int h = D * (dx + dy) + (D2 - 2 * D) * fmin(dx, dy);
    return h;
}

// fCost function:
int fCost(Cell *startNode, Cell *targetNode, Cell *currentNode)
{

    return gCost(startNode, currentNode) + hCost(targetNode, currentNode);
}

int inList(LinkedList *list, Cell *node)
{
    Node *currentNode = list->head;
    for (int i = 0; i < list->count; i++)
    {
        if (currentNode->cell == node)
            return TRUE;
        currentNode = currentNode->next;
    }
    return FALSE;
}

int inOpen(Heap *h, Cell *node)
{

    for (int i = 0; i < h->size; i++)
    {
        if (node == h->arr[i])
            return TRUE;
    }
    return FALSE;
}