#include "heap.h"


Heap* createHeap(int* nums) {
    Heap* h  = (Heap*) malloc(sizeof(Heap*));

    //always check if the pointer is null
    if (h == NULL) {
        printf("Error allocating the memory for the heap");
        return NULL;
    }

    h->size = 0;
    int i;
    for (i = 0; i < sizeof(*nums) / sizeof(int); i++) {
        h->arr[i] = nums[i];
    }
    h->size = i;
    while (i >=0) {
        heapify(h,i);
        i--;
    }
    return h;
}

void heapify(Heap *h, int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index; 

       // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && h->arr[left] < h->arr[index])
        min = left;
    if (right != -1 && h->arr[right] < h->arr[index])
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        int temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min heap
        heapify(h, min);
}
}

void insertHelper(Heap* h, int child) {
    int parent = (child - 1) / 2 ;

    if (h -> arr[parent] > h -> arr[child]) {
        //swap if child is smaller than parent
        int temp = h->arr[child];
        h->arr[parent] = h->arr[child];
        h -> arr[child] = temp;

        insertHelper(h, parent);
    }
}

int popHeap(Heap* h) {
    int poppedItem;

    if (h -> size == 0) {
        printf("\nHeap is empty");
        return -1;
    }
    //store popped item
    poppedItem = h->arr[0];

    //swap popped item with the last node
    h->arr[0] = h -> arr[h -> size - 1];
    h -> size--;

    heapify(h,0);
    return poppedItem;
}

void pushHeap(Heap* h, int data) {
    if (h -> size < HEAP_CAPACITY) {
        h -> arr[h -> size] = data;

        insertHelper(h, h->size);
        h -> size++;
    }
}