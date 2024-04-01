#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

// Function to create an empty linked list
LinkedList *createLinkedList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list)
    {
        list->head = NULL;
        list->count = 0;
    }
    return list;
}

// Function to add a node to the end of the linked list
void addNode(LinkedList *list, Cell *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode)
    {
        newNode->cell = data;
        newNode->next = NULL;
        if (list->head == NULL)
        {
            list->head = newNode;
            newNode->key = list->count;
            list->count++;
        }
        else
        {
            Node *current = list->head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
            newNode->key = list->count;
            list->count++;
        }
    }
    else
    {
        printf("Memory allocation failed!\n");
    }
}

// Function to delete a node with given data from the linked list
int deleteNode(LinkedList *list, Node *data)
{
    if (list->head != NULL)
    {
        Node *current = list->head;
        Node *previous;
        while (current != NULL)
        {
            if (current == data)
            {
                if (current == list->head)
                {
                    list->head = current->next;
                    free(current);
                    list->count--;
                    return EXIT_SUCCESS;
                }
                else
                {
                    previous->next = current->next;
                    free(current);
                    list->count--;
                    return EXIT_SUCCESS;
                }
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
        return EXIT_FAILURE; // Node with given data not found
    }
    else
        printf("List is Empty");
        return EXIT_FAILURE;
}

// Function to find a node with given data in the linked list
Node *findNode(LinkedList *list, Cell *cell)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->cell == cell)
        {
            return current; // Node found
        }
        current = current->next;
    }

    return NULL; // Node with given data not found
}

//// Function to display the elements of the linked list
void displayList(LinkedList *list)
{
    Node *current = list->head;
    printf("\n");
    if (list -> head == NULL) printf("NULL list");
    while (current != NULL)
    {
        printf("%d ", current->key);
        printf("[%d][%d] -> ", current ->cell ->coordinates[0], current ->cell ->coordinates[1]);
        current = current->next;
    }
    printf("\n");
}
//
//// Function to free memory allocated for the linked list
// void destroyList(LinkedList* list) {
//     Node* current = list->head;
//     Node* next;
//
//     while (current != NULL) {
//         next = current->next;
//         free(current);
//         current = next;
//     }
//
//     free(list);
// }