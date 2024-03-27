#include <stdio.h>
#include <stdlib.h>
#include "gridStructure.h"

//general process of the astar algorithm
/*
1. Initialize the open list
2.  Initialize the closed list
    put the starting node on the open 
    list (you can leave its f at zero)
3.  while the open list is not empty
    a) find the node with the least f on 
       the open list, call it "q"
    b) pop q off the open list
  
    c) generate q's 8 successors and set their 
       parents to q
   
    d) for each successor
        i) if successor is the goal, stop search
        
        ii) else, compute both g and h for successor
          successor.g = q.g + distance between 
                              successor and q
          successor.h = distance from goal to 
          successor (we will do this usign diagonal distance)
          
          successor.f = successor.g + successor.h
        iii) if a node with the same position as 
            successor is in the OPEN list which has a 
           lower f than successor, skip this successor
        iV) if a node with the same position as 
            successor  is in the CLOSED list which has
            a lower f than successor, skip this successor
            otherwise, add  the node to the open list
     end (for loop)
  
    e) push q on the closed list
    end (while loop)*/

    void aStarSearch();

    //we will use a diagonal distance heuristic.
    double calculateHeuristic(int row, int col, Cell* pass);

    void tracePath();

    int isValid();

    int isUnBlocked();

    int isDestination(int row, int col, Cell* pass);