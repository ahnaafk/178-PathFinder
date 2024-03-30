#include "heap.h"

Heap *createHeap()
{
    Heap *h = (Heap *)malloc(sizeof(Heap *));

    // always check if the pointer is null
    if (h == NULL)
    {
        printf("Error allocating the memory for the heap");
        return NULL;
    }

    h->size = 0;
    int i;
    for (i = 0; i < HEAP_CAPACITY; i++)
    {
        h->arr[i] = malloc(sizeof(Cell *));
    }
    h->size = i;
    while (i >= 0)
    {
        heapify(h, i);
        i--;
    }
    return h;
}

void heapify(Heap *h, int parent)
{
    int leftChild = parent * 2 + 1;
    int rightChild = parent * 2 + 2;
    int min = parent;

    // Checking whether our leftChild or rightChildChild element
    // is at rightChild index or not to avoid index error
    if (leftChild >= h->size || leftChild < 0)
        leftChild = -1;
    if (rightChild >= h->size || rightChild < 0)
        rightChild = -1;

    // store leftChild or rightChild element in min if any of these is smaller that its parent
    if (leftChild != -1 && h->arr[leftChild]->f_cost < h->arr[parent]->f_cost)
    {
        min = leftChild;
    }//if the f-costs are equivilent, then compare the h-costs. 
    else if (leftChild != -1 && h->arr[leftChild]->f_cost == h->arr[parent]->f_cost)
    {
        if (h->arr[leftChild]->h_cost < h->arr[parent]->h_cost) min = leftChild;
    }
    if (rightChild != -1 && h->arr[rightChild] < h->arr[parent]) {
        min = rightChild;
    }  else if (rightChild != -1 && h->arr[rightChild]->f_cost == h->arr[parent]->f_cost)
    {
        if (h->arr[rightChild]->h_cost < h->arr[parent]->h_cost) min = rightChild;
    }
    // Swapping the nodes
    if (min != parent)
    {
        Cell* temp = h->arr[min];
        h->arr[min] = h->arr[parent];
        h->arr[parent] = temp;

        // recursively calling for their child elements to maintain min heap
        heapify(h, min);
    }
}

void insertHelper(Heap *h, int child)
{
    int parent = (child - 1) / 2;

    if (h->arr[parent]->f_cost > h->arr[child]->f_cost)
    {
        // swap if child is smaller than parent
        Cell* temp = h->arr[child];
        h->arr[parent] = h->arr[child];
        h->arr[child] = temp;

        //work your way up the heap to make sure that the heap is still in order. 
        insertHelper(h, parent);
    }
}

Cell* popHeap(Heap *h)
{
    Cell* poppedItem;

    if (h->size == 0)
    {
        printf("\nHeap is empty");
        return NULL;
    }
    // store popped item
    poppedItem = h->arr[0];

    // swap popped item with the last node
    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    heapify(h, 0);
    return poppedItem;
}

void pushHeap(Heap *h, Cell* data)
{
    if (h->size < HEAP_CAPACITY)
    {
        h->arr[h->size] = data;

        insertHelper(h, h->size);
        h->size++;
    }
}