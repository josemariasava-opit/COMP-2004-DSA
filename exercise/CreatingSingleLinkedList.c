#include <stdio.h>
#include <stdlib.h>
#include <nodeoflist.h> 

int main() { 

    struct node *head = malloc(sizeof(struct node)); 
    head->data = 45; 
    head->link = NULL; 

    struct node *current = malloc(sizeof(struct node)); 
    current->data = 98; 
    current->link = NULL; 
    head->link = current; // now first node points to second node ( current )

    current = malloc(sizeof(struct node)); 
    current->data = 3; 
    current->link = NULL; 

    head->link->link = current; 


    return 0; 
}