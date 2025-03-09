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
#include <stdbool.h> /* included to handle bool type values*/

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

    /* Loop untile user choice is 7 */
    while (run)
    {
        /* Print application menù */
        printf("\nEnter your choice: \n"
               "[1] push    : Insert item x on the front end of the deque\n"
               "[2] pop     : Remove the front item from the deque\n"
               "[3] inject  : Insert item x on the rear end of the deque\n"
               "[4] eject   : Remove the rear item from the deque and return it\n"
               "[5] print   : Prints the contents of the deque from fron to rear\n"
               "[6] empty   : Clears the contents of the deque\n"
               "[7] exit    : Exit the Deque program\n"
        );
        /* Ask user the choice from the menù */
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        /* Switch to handle all the cases*/
        switch (choice)
        {
        case 1:
            /* Ask user to input  data */
            printf("Enter value to push : ");
            scanf("%d", &data);
            push(pDeque,data);
            break;
        
        case 2:
            data = pop(pDeque);
            printf("Pop element %d from front of the deque \n", data);
            break;  
        
        case 3:
            /* Ask user to input  data */
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
            /* Free memory of the deque when user wants to exit*/
            makeEmpty(pDeque); 
            printf("--- Exit the program ---\n");
            run = false; /* stop the loop*/
            break; 

        default:
            /* Default case to handle invalud choice from user*/
            printf("Invalid choice \n"); 
            break;
        }  
    }
    return 0; 
}

/*
* Function name     :   createNode
* Arguments         :   data        = Integer value, data of structure Node
* Return value/s    :   newNode     = Pointer to the allocated memory for Node
* Remarks           :   Create a new Node*, check the correct memory allocation and assign to it data, prev node and nex node.  
*/
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

/*
* Function name     :   createDeque
* Arguments         :   ---
* Return value/s    :   newDeque     = Pointer to the allocated memory for deque
* Remarks           :   Create a new Deque ( double end-ended queue) and check the correct
*                       memory allocation. 
*                       Both pointers for front-rear are initializated to NULL, so the deque starts empty. 
*/
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

/*
* Function name     :   push
* Arguments         :   pDeque       = Pointer to deque structure
*                   :   data         = Integer value for the new  Node
* Return value/s    :   ---
* Remarks           :   Create a new Node with the given data, check if the deque front is NULL and set 
*                       both front and rear to newNode created. 
*                       If the deque is not empty, adjust pointers to insert newNode
*/
void push(Deque* pDeque, int data){

    Node* newNode = createNode(data);

    if (pDeque->front == NULL) { /* Empty Deque condition*/
        /* Set both front and reas as newNode*/
        pDeque->front = pDeque->rear = newNode;
    } else { /* Deque not empty*/
        newNode->next = pDeque->front; /* Update next of NewNode*/
        pDeque->front->prev = newNode; /* Update the current front node prev to newNode*/
        pDeque->front = newNode; /* Update Deque front to point newNode*/
    }
    /* Notify */
    printf("Push action completed! \n");
}

/*
* Function name     :   pop
* Arguments         :   pDeque       = Pointer to deque structure
* Return value/s    :   data         = removed data 
* Remarks           :   First check the front of the Deque, if empty notify and return 1
*                       Use a tempNode to extract the data, updates the new front and check if becomes 
*                       empty after removal.
*/
int pop(Deque* pDeque){
    if (pDeque->front == NULL)
    {
        printf("Deque is Empty! First insert an element \n");
        return(1);
    }

    /* Temp to store the data*/
    Node* tempNode = pDeque->front; 
    int data = tempNode->data;
    
    /* Move front of deque to the next node*/
    pDeque->front = pDeque->front->next;

    /* Check if becomes empty*/
    if (pDeque->front == NULL)
    {
        /* If empty set rear as NULL*/
        pDeque->rear = NULL; 
    }
    else{
        /* Otherwise update the new front prev to NULL*/
        pDeque->front->prev = NULL;
    }
    
    /* Free memory allocation */
    free(tempNode);
    return data; 
}

/*
* Function name     :   inject
* Arguments         :   pDeque       = Pointer to deque structure
*                   :   data         = Integer value for the new  Node
* Return value/s    :   ---
* Remarks           :   Create a new Node with the given data, check if the deque rear is NULL and set 
*                       both front and rear to newNode created. 
*                       If the deque is not empty, adjust pointers to insert newNode
*/
void inject(Deque* pDeque, int data){
    Node* newNode = createNode(data);

    if (pDeque->rear == NULL)/* Empty Deque condition*/
    {  /* Set both front and reas as newNode*/
        pDeque->front = pDeque->rear = newNode;
    }
    else/* Deque not empty*/
    {
        newNode->prev = pDeque->rear; /* Update prev of NewNode*/
        pDeque->rear->next = newNode; /* Update the current rear node next to newNode*/
        pDeque->rear = newNode; /* Update Deque rear to point newNode*/
    }
    /* Notify */
    printf("Inject action completed! \n");
}

/*
* Function name     :   inject
* Arguments         :   pDeque       = Pointer to deque structure
* Return value/s    :   data         = removed data 
* Remarks           :   First check the rear of the Deque, if empty notify and return 1
*                       Use a tempNode to extract the data, updates the new front and check if becomes 
*                       empty after removal.
*/
int eject(Deque* pDeque){
    if(pDeque->rear == NULL){
        printf("Deque is Empty! First insert an element \n");
        return(1);
    }

    /* Temp to store the data*/
    Node* tempNode = pDeque->rear; 
    int data = tempNode->data; 

    /* Move rear of deque to prev node*/
    pDeque->rear = pDeque->rear->prev; 

    /* Check if becomes empty*/
    if (pDeque->rear == NULL)
    {
        /* If empty set front as NULL*/
        pDeque->front = NULL; 
    }
    else
    {
        /* Otherwise update the new rear next to NULL*/
        pDeque->rear->next = NULL;
    }
    
        /* Free memory allocation */
        free(tempNode);
        return data; 
} 

/*
* Function name     :   printDeque
* Arguments         :   pDeque       = Pointer to deque structure
* Return value/s    :   ---
* Remarks           :   Print deque from front to rear, loop as long as there nodes in the deque
*/
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
        printf("%d ", currentNode->data);
        currentNode = currentNode->next; 
    }
    printf("\n");
}

/*
* Function name     :   makeEmpty
* Arguments         :   pDeque       = Pointer to deque structure
* Return value/s    :   ---
* Remarks           :   Free memory and empty the deque, loop continues as long as there are nodes in 
*                       the deque. Store current front in a tempNode and move the front to next node. 
*                       at each iteration of the loop free memory of tempNode 
*/
void makeEmpty(Deque* pDeque){
    while (pDeque->front != NULL)
    {
        Node* tempNode = pDeque->front; 
        /* Move front to next node */
        pDeque->front = pDeque->front->next; 
        /* Free memory of the removed node*/
        free(tempNode);
    }
    /* Update rear to null*/
    pDeque->rear = NULL; 
    /* Notify*/
    printf("Deque cleared !\n"); 
}