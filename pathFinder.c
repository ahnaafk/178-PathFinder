#include "pathFinder.h"
#include <math.h>

/*
Per Buba's structure
1. Check closest target -> minimize h-cost
2. if (dest) -> check if we have their passenger? pathfinder(target): go next
3. if (pass) -> pathfinder(pass);
*/

void astar(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *start, Cell *passengers[], Cell *destinations[])
{
    // // 1. Check closest target
    // int min; // holder for closest target
    // Cell *minCell = findMinTarget(start, passengers, destinations);
    // if (minCell[DESTINATION] == TRUE ) {
    //     if (inList(LinkedList, minCell)) pathFinder(grid, start, minCell);
    // } else if (minCell[PASSENGER] == TRUE) pathFinder(grid, start, minCell); 
}

// bruh gonna have to cahgne this whole function when the linked list is implemented.
// check both lists for the minimum h-cost.

Cell *findMinTarget(Cell *start, Cell *passengers[], Cell *destinations[])
{

    // possible objectives
    // 1. a passenger that we haven't picked up
    // 2. a destination of a passenger that we HAVE picked up.

    // realistically, we shouldn't check both lists and instead check the passengers we DONT have, and the destinations of the passengers we have.
    // TODO for Ethan, figure out a way to take the busList (passengers we have), and create a list with the passengers we don't have, and the destinations of hte passengers that we do have.
    // int passenger_count = PASSENGER; // TODO for ETHAN: change to the count of the linked list!
    // int minCost;
    // Cell *minCell = malloc(sizeof(Cell *));
    // minCell = passengers[0];
    // minCost = hCost(start, minCell);
    // for (int i = 0; i < passenger_count; i++)
    // {
    //     Cell *tempCell = passengers[i];
    //     int tempCost = hCost(start, minCell);
    //     if (tempCost < minCost)
    //     {
    //         minCost = tempCost;
    //         minCell = tempCell;
    //     }
    // }
}

// finds a path to a target node, returns the new starting node.
Cell *pathFinder(Cell *grid[GRID_SIZE][GRID_SIZE], Cell *startNode, Cell *targetNode)
{

    // // Initialize openSet
    // Heap *openSet = createHeap();
    // // Initialize closedSet
    // // TODO: linked list goes here for closed set!!!!!

    // // Add startNode to open set
    // pushHeap(openSet, startNode);

    // while (openSet->size > 0)
    // {
    //     // Take smallest f node or if equal take lowest h
    //     Cell *currentNode = popHeap(openSet);

    //     // TOOD: add current node to closed set (linked list)

    //     // if the coordinates match between the current node and the target node, we have a match!
    //     if (currentNode->coordinates[0] == targetNode->coordinates[0] && currentNode->coordinates[1] == targetNode->coordinates[1])
    //     {
    //         retracePath(currentNode, targetNode);
    //         return currentNode; // not sure if we return this.
    //     }

    //     // get each neighbour of the current node.
    //     for (int x = -1; x <= 1; x++)
    //     {
    //         for (int y = -1; y <= 1; y++)
    //         {
    //             if (x == 0 && y == 0)
    //                 continue;
    //             int checkX = currentNode->coordinates[0] + x;
    //             int checkY = currentNode->coordinates[1] + y;

    //             // if the new x and y are valid, then check the neighbour at that location
    //             if (checkX >= 0 && checkX < GRID_SIZE && checkY >= 0 && checkY < GRID_SIZE)
    //             {
    //                 Cell *neighbour = grid[checkX][checkY];
    //                 // if the neighbour is construction, or is in the closed list, then skip iteration
    //                 if (neighbour->cellData[CONSTRUCTION] == TRUE || isClosed(neighbour))
    //                     continue;

    //                 // if the new path to neighbour is shorter OR the neighbour is not in the open then...

    //                 // TODO: verify this logic
    //                 // TODO create the isOpen function once linked list is created.
    //                 if (gCost(currentNode, neighbour) < neighbour->g_cost || !isOpen(neighbour))
    //                 {
    //                     neighbour->f_cost = fCost(startNode, targetNode, neighbour);
    //                     neighbour->parent = currentNode;
    //                     if (!isOpen(neighbour))
    //                         pushHeap(openSet, neighbour);
    //                 }
    //             }
    //         }
    //     }
    // }
}

/*
        //push neighbours of the popped node to the heap
        for (int i = 1; i < openSet -> size; i++){
            openSetF = fCost(startNode, targetNode, openSet[i]);
            currentF = fCost(startNode, targetNode, currentNode);
            openSetH = hCost(targetNode, openSet[i]);
            currentH = hCost(targetNode, currentNode);

            if ( openSetF < currentF || (openSetF == currentF && openSetH < currentH){
                currentNode = openSet[i];
            }

            //remove node from openSet and add to closed set
            remove(currentNode, openSet); FIX THIS
            add(currentNode, closedSet); FIX THIS

            //Check if current node is target node
            if (currentNode coordinates == targetNode coordinates){ FIX THIS
                //retrace path function??
                return;
            }

            for (int i = 0; i < 8; i ++){
                List neighbour = getNeighbours(currentNode);

                if((neighbour[i]->cellData[1] != 1) || neighbour[i] is in closedSet) FIX THIS
                    continue;

                int movingCost = gCost(startNode, currentNode) + getDistance(currentNode, neighbour[i]);
                if (movingCost < gCost(startNode, neighbour[i]) || open set doesnt contain neighbour[i]){ FIX THIS
                    neighbour[i]->g = movingCost;                         FIX THIS
                    neighbour[i]->h = hCost(targetNode, neighbour[i]);    FIX THIS
                    neighbour[i]->parent = currentNode;                   FIX THIS

                    if(open set doesnt have neighbour[i])
                        add neighbour[i] to openSet
                }
            }
        }

*/
void retracePath(Cell *startNode, Cell *endNode)
{
    // List* path = newList(); FIX THIS
    // Cell currentNode = endNode;

    // while(currentNode != startNode){
    // add currentNode to path;               FIX THIS
    // currentNode = currentNode->parent;
    //}
    // Reverse path now because it's in opposite order
}

// int isClosed(Cell* node, LinkedList closedList ) {
//     //check if node is in the closed list.
// }

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
