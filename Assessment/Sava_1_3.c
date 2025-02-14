/*
* A deque is a data structure that holds a list of elements and implements the following
* operations:
* - push(x): Insert item x on the front end of the deque
* - pop(): Remove the front item from the deque and return it
* - inject(x): Insert item x on the rear end of the deque
* - eject (x): Remove the rear item from the deque and return it
* - print(): prints the contents of the dequeue from front to rear
* - makeEmpty(): clears the contents of the dequeue
* Your task is to write a program that implements the first four operations above on a deque data
* structure in O(1) time. You should appropriately choose the data structure (array versus linked
* list) for your deque that allows you to implement these operations in O(1) time. You should also
* define a menu driven command-line interface that allows you to select the above operations.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Struct to represent the single node of the linked list*/
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
}Node;

/* Struct for the Deque, one node for front and one for the rear*/
typedef struct Deque{
    Node* front; 
    Node* rear;
}Deque; 

/*Function prototypes*/
Node* createNode(int data);
Deque* createDeque();
void push(Deque* pDeque, int data); /* Insert item x on the front end of the deque*/
int pop(Deque* pDeque); /* Remove the front item from the deque and return it*/
void inject(Deque* pDeque, int data); /* Insert item x on the rear end of the deque*/
int eject(Deque* pDeque); /* Remove the rear item from the deque and return it*/
void printDeque(Deque* pDeque); /* prints the contents of the deque from front to rear*/
void makeEmpty(Deque* pDeque); /* clears the contents of the deque*/


int main(){

    /* Local vars */
    Deque* pDeque = createDeque();
    int choice, data; 
    bool run = true;

    while (run)
    {
        printf("\nEnter your choice: \n"
               "[1] push    : Insert item x on the front end of the deque\n"
               "[2] pop     : Remove the front item from the deque\n"
               "[3] inject  : Insert item x on the rear end of the deque\n"
               "[4] eject   : Remove the rear item from the deque and return it\n"
               "[5] print   : Prints the contents of the deque from fron to rear\n"
               "[6] empty   : Clears the contents of the deque\n"
               "[7] exit    : Exit the Deque program\n"
        );

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push : ");
            scanf("%d", &data);
            push(pDeque,data);
            break;
        
        case 2:
            data = pop(pDeque);
            printf("Pop element %d from front of the deque \n", data);
            break;  
        
        case 3:
            printf("Enter the value to inject: ");
            scanf("%d", &data); 
            inject(pDeque, data); 
            break;
        
        case 4: 
            data = eject(pDeque); 
            printf("Eject element %d from rear of the deque \n", data); 
            break; 

        case 5: 
            printDeque(pDeque); 
            break; 

        case 6: 
            makeEmpty(pDeque); 
            break; 

        case 7: 
            makeEmpty(pDeque); 
            printf("--- Exit the program ---\n");
            run = false;
            break; 

        default:
            printf("Invalid choice \n"); 
            break;
        }
        
    }
    




    return 0; 
}


Node* createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed! \n");
        exit(1);
    }
    newNode->data = data; 
    newNode->next = NULL;
    newNode->prev = NULL; 
    
    return newNode; 
}

Deque* createDeque(){
    Deque* newDeque = malloc(sizeof(Deque));
    if (newDeque == NULL)
    {
        printf("Memory allocation failed \n");
        exit(1);
    }

    newDeque->front = newDeque->rear = NULL; 
    return newDeque; 
}

/* Insert item x on the front end of the deque*/
void push(Deque* pDeque, int data){

    Node* newNode = createNode(data);

    if (pDeque->front == NULL) {
        pDeque->front = pDeque->rear = newNode;
    } else {
        newNode->next = pDeque->front;
        pDeque->front->prev = newNode;
        pDeque->front = newNode;
    }

    printf("Push action completed! \n");
}

/* Remove the front item from the deque and return it*/
int pop(Deque* pDeque){
    if (pDeque->front == NULL)
    {
        printf("Deque is Empty! First insert an element \n");
        return(1);
    }

    Node* tempNode = pDeque->front;
    int data = tempNode->data;

    pDeque->front = pDeque->front->next;

    if (pDeque->front == NULL)
    {
        pDeque->rear = NULL; 
    }
    else{
        pDeque->front->prev = NULL;
    }
    
    /* Free memory allocation */
    free(tempNode);
    return data; 
}

/* Insert item x on the rear end of the deque*/
void inject(Deque* pDeque, int data){
    Node* newNode = createNode(data);

    if (pDeque->rear == NULL)
    {
        pDeque->rear = pDeque->rear = newNode;
    }
    else
    {
        newNode->prev = pDeque->rear; 
        pDeque->rear->next = newNode; 
        pDeque->rear = newNode; 
    }
    printf("Inject action completed! \n");
}

/* Remove the rear item from the deque and return it*/
int eject(Deque* pDeque){
    if(pDeque->rear == NULL){
        printf("Deque is Empty! First insert an element \n");
        return(1);
    }

    Node* tempNode = pDeque->rear; 
    int data = tempNode->data; 

    pDeque->rear = pDeque->rear->prev; 

    if (pDeque->rear == NULL)
    {
        pDeque->front = NULL; 
    }
    else
    {
        pDeque->rear->next = NULL;
    }
    
        /* Free memory allocation */
        free(tempNode);
        return data; 
} 

void printDeque(Deque* pDeque){

    if (pDeque->front == NULL)
    {
        printf("Deque is Empty! First insert an element \n");
        return;
    }

    /* Get current node and loop until the front is null*/
    Node* currentNode = pDeque ->front;
    printf("Printing Deque from front to rear\n");
    while (currentNode != NULL)
    {
        printf("%d <-> ", currentNode->data);
        currentNode = currentNode->next; 
    }
    printf("\n");
}

void makeEmpty(Deque* pDeque){
    while (pDeque->front != NULL)
    {
        Node* tempNode = pDeque->front; 
        /* Shift front*/
        pDeque->front = pDeque->front->next; 
        /* Free memory*/
        free(tempNode);
    }
    pDeque->rear = NULL; 
    printf("Deque cleared !\n"); 
}