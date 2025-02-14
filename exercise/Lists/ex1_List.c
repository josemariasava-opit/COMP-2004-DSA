/*
Exercise 1: Basic Linked List Creation

Goal: Create a simple linked list with a single node.

    Define a structure for a node that contains an integer value and a pointer to the next node.
    Write a function to create a new node with a given integer value.
    Write a main function to create a linked list with one node and print the value stored in that node.
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure 
struct Node{
    int data; 
    struct Node *next; 
};

// create new noe method 
struct Node* createNode (int data ){ 
    struct Node *pNode = malloc(sizeof(struct Node)); 

    if(pNode == NULL){ 

        printf("Cannot allococate memory \n"); 
        return 0; 
    }
    // assign value 
    pNode->data = data; 
    pNode->next = NULL; // points to null because is the only node 
    return pNode; 
}

int main(){ 

    struct Node *head = createNode(10);
    printf("Node data : %d\n", head->data);


    return 0; 
}