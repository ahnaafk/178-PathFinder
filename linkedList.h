#include "heap.h"
// Define the structure for the node in the linked list
typedef struct Node {
    Cell* data;
    struct Node* next;
    int key;
} Node;

// Define the structure for the linked list itself
typedef struct LinkedList {
    Node* head;
} LinkedList;

// Function prototypes
LinkedList* createLinkedList();
void addNode(LinkedList* list, Node* data);
int deleteNode(LinkedList* list, Node* data);
Node* findNode(LinkedList* list, Node* data);
void displayList(LinkedList* list);
void destroyList(LinkedList* list);

