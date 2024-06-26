#include <stdio.h>
#include <stdlib.h>
#include "gridStructure.h"

#define HEAP_CAPACITY 70 // size = grid size - construction points,

// min Heap implementation

// denote that:
/*
parent(i) = (i-1)/2
left_child(i) = 2*i + 1
right_child(i) = 2*i + 2
*/

typedef struct heap
{
    Cell *arr[HEAP_CAPACITY];
    int size;
} Heap;

// Creates a heap and returns the pointer to the heap structure.
Heap *createHeap();

// Pop the min value from the heap
Cell *popHeap(Heap *h);

// Push a value onto the heap
void pushHeap(Heap *h, Cell *data);

void insertHelper(Heap *h, int child);

// Fix the heap
void heapify(Heap *h, int index);