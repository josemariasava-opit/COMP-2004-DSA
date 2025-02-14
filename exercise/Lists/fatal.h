#include <stdio.h>
#include <stdlib.h>

// Node structure 
struct Node{
    int data; 
    struct Node *next; 
};

// create new node/ cell method 
struct Node* createNode (int data ){ 
    struct Node *pNode = (struct Node*)malloc(sizeof(struct Node)); 

    if(pNode == NULL){ 

        printf("Cannot allococate memory \n"); 
        return 0; 
    }
    // assign value 
    pNode->data = data; 
    pNode->next = NULL; // points to null because is the only node 
    return pNode; 
}

// print the list

void printList(struct Node *pHeader){
    // set current to header pointer  
    struct Node *current = pHeader; 
    // Loop until current is NULL (Last element of the LIst)
    while(current != NULL) { 
        // print data of the current element 
        printf("%d -> ", current->data); 
        // assign to current the next node address 
        current = current->next;
    }
    // notify by printing NULL at the end of the list 
    printf("NULL\n");
}