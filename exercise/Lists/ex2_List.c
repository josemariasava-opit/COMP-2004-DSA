/*
Exercise 2: Traverse the Linked List

Goal: Traverse the linked list to print all its values.

    Modify your linked list structure to hold multiple nodes (i.e., create at least 3 nodes).
    Write a function that loops through the list and prints each value.
    Print the linked list values in the main function.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fatal.h>

int main(){

    struct Node *head = createNode(10); 
    head->next = createNode(100); 
    head->next->next = createNode(1000); 

    printList(head);
    return 0; 
}