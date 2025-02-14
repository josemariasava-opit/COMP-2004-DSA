#include <stdio.h> // I/O management 
#include <stdlib.h> // required to call malloc and dynamic memory allocation function 

// Self referential structure --> Is a structure which contains a pointer to a structure of the same type 

// node of a linked list - uses self referential structure 
/*     ---------    ---------           */
/*     | Data  |    | Data  |           */
/*     |  ---  |    |  ---  |           */
/*     |  Link |--> |  Link |--> NULL   */
/*     ---------    ---------           */

struct node{

    int data; // data can be of any kind : integer, float 
    struct node *link; // Link is the pointer of another node 
};

int main(){ 

    struct node *head = NULL; // this point to the head of the list - first node 
    head = (struct node *)malloc(sizeof(struct node)); // calling malloc to allocate memory for struct node - helps to create a node 

    head ->data = 45; // assing int value 45 to data 
    head ->link = NULL; // assign NULL for next node of the linked list 

    printf("data of head node : %d  \n", head->data ); 
    printf("Momeory locaton of head node : %p \n", head->link); 

    return 0; 
}

