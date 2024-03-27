#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 70; //size = grid size - construction points,

//min Heap implementation

//denote that:
/*
parent(i) = (i-1)/2
left_child(i) = 2*i + 1
right_child(i) = 2*i + 2
*/

typedef struct heap
{
    int *arr;
    int size;
    int capacity;
} Heap;

//Creates a heap and returns the pointer to the heap structure. 
Heap* createHeap(int capacity, int* nums);

//Pop the min value from the heap
int popHeap(Heap* h);

//Push a value onto the heap
void pushHeap(Heap* h, int data);

void pushHelper(Heap* h, int index);

//Fix the heap
void heapify(Heap *h, int index);