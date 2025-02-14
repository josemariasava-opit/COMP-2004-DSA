#include <stdio.h>
#include <stdlib.h>

// create the struct for the single node/cell 
struct Node{ 
    int data;  // data part, in this case integer 
    struct Node *next; // pointer to the struct if next node 
}; 

// method to print all the node inside the list 
void printLinkedList(struct Node *p){

    while (p!= NULL){  // loop until p value is null ( last element of the list )

        printf("%d \n", p->data); // print the data member of pointer p 
        p = p->next;  // assign to p the address of next node 
    }
}

int main() { 

    // allocate memory 

    struct Node *head; 
    struct Node *one = malloc(sizeof(struct Node));
    struct Node *two = malloc(sizeof(struct Node));
    struct Node *three = malloc(sizeof(struct Node));

    // assign data values 
    one->data = 1; 
    two->data = 2; 
    three->data = 3;

    // Connect nodes 
    one->next = two;  
    two->next = three; 
    three->next = NULL; // last element points to null 

    // save address of the first node to head - in this way we can access the list 
    head->next = one; 

    printLinkedList(head); 

    return 0; 
}