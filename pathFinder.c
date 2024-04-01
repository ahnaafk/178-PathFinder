#include "pathFinder.h"
#include <math.h>

// Finds min target from starting cell, finds shortest path from starting
void astar(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *start, LinkedList *masterList[4], LinkedList *listOfPaths[35])
{
    Cell *startingCell = start;
    Cell *targetCell;
    // Loop while targets are still available
    while (masterList[TARGETLIST]->head != NULL)
    {
        // Find the next target
        targetCell = findMinTarget(startingCell, masterList[TARGETLIST]);

        // Finds the path to next target and sets the target to new starting cell
        startingCell = pathFinder(grid, startingCell, targetCell, masterList, listOfPaths);

        //Passenger pickup routine:
        if (startingCell->cellData[PASSENGER] == 1)
        {
            //Add the passenger's destination to the target list and add the passenger to the buslist
            addNode(masterList[TARGETLIST], startingCell->destination);
            addNode(masterList[PASSONBUS], startingCell);

            //Delete the passenger from the idlelist and delete it from the target list. 
            deleteNode(masterList[IDLEPASS], findNode(masterList[IDLEPASS], startingCell));
            deleteNode(masterList[TARGETLIST], findNode(masterList[TARGETLIST], startingCell));
        }
        //Passenger dropoff routine
        else if (startingCell->cellData[DESTINATION] == 1)
        {
            //Delete the destination off of the target list and delete the passenger from the bus list . 
            deleteNode(masterList[TARGETLIST], findNode(masterList[TARGETLIST], startingCell));
            deleteNode(masterList[PASSONBUS], findNode(masterList[PASSONBUS], startingCell));
        }
    }
}

Cell *findMinTarget(Cell *start, LinkedList *targetList)
{

    // possible objectives
    // 1. a passenger that we haven't picked up
    // 2. a destination of a passenger that we HAVE picked up.

    // realistically, we shouldn't check both lists and instead check the passengers we DONT have, and the destinations of the passengers we have.
    // TODO for Ethan, figure out a way to take the busList (passengers we have), and create a list with the passengers we don't have, and the destinations of hte passengers that we do have.
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
Cell *pathFinder(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *startNode, Cell *targetNode, LinkedList *masterList[4], LinkedList *listOfPaths[35])
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
            retracePath(startNode, currentNode, masterList, listOfPaths);
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
                        neighbour->h_cost = hCost(startNode, targetNode);
                        neighbour->g_cost = gCost(startNode, targetNode);
                        neighbour->parent = currentNode;
                        if (!inOpen(openSet, neighbour))
                            pushHeap(openSet, neighbour);
                    }
                }
            }
        }
    }
    return NULL;
}

void retracePath(Cell *startCell, Cell *endCell, LinkedList *masterList[4], LinkedList *pathList[35])
{

    Cell *currentCell = endCell;
    // printf("Starting Cell: [%d][%d] \n", startCell ->coordinates[0], startCell ->coordinates[1]);
    int i = 0;
    while (pathList[i] != NULL)
        i++; // find an empty path within the path list.
    pathList[i] = createLinkedList();

    // Create a templist with all the parents of the nodes. Head -> endNode
    while (currentCell != startCell)
    {
        addNode(pathList[i], currentCell);
        currentCell = currentCell->parent;
    }

    // Reverse path now because it's in opposite order.
    // reverseList(tempList);
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