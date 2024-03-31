#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

// Function to create an empty linked list
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list) {
        list->head = NULL;
    }
    return list;
}

// Function to add a node to the end of the linked list
void addNode(LinkedList* list, Node* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
        if (list->head == NULL) {
            list->head = newNode;
        } else {
            Node* current = list->head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            list->count++;
        }
    } else {
        printf("Memory allocation failed!\n");
    }
}

// Function to delete a node with given data from the linked list
int deleteNode(LinkedList* list, Node* data) {
    if(list->head !=NULL) {
        Node *current = list->head;
        Node *previous = NULL;
        int key = data->key;
        while (current != NULL) {
            if (current->key == key) {
                if(current->key==list->head->key){
                    list->head=current->next;
                    free(current);
                    return EXIT_SUCCESS;
                    list->count--;
                }
                else {
                    previous->next = current->next;
                    free(current);
                    return EXIT_SUCCESS;
                    list->count--;
                }
            }
            else {
                previous = current;
                current = current->next;
            }
        }
        return EXIT_FAILURE; // Node with given data not found
    }
    else
        printf("List is Empty");
}

// Function to find a node with given data in the linked list
Node* findNode(LinkedList* list, Node* data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->key == data->key) {
            return current; // Node found
        }
        current = current->next;
    }

    return NULL; // Node with given data not found
}

//// Function to display the elements of the linked list
//void displayList(LinkedList* list) {
//    Node* current = list->head;
//
//    while (current != NULL) {
//        printf("%d ", current->data->);
//        current = current->next;
//    }
//    printf("\n");
//}
//
//// Function to free memory allocated for the linked list
//void destroyList(LinkedList* list) {
//    Node* current = list->head;
//    Node* next;
//
//    while (current != NULL) {
//        next = current->next;
//        free(current);
//        current = next;
//    }
//
//    free(list);
//}