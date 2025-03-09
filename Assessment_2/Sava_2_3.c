/*
a) Given two binary trees, return true if and only if they are structurally identical (they have the 
same shape, but their nodes can have different values). 
b) Given two binary trees, return true if they are identical (they have nodes with the same values, 
arranged in the same way)
*/

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_from_list.c"
#include <stdbool.h>

/*Function prototypes*/
ElementType structurally_identical(Node T1,Node T2);
ElementType are_identical(Node T1,Node T2); 

int main()
{   
    int n;
    printf("Enter the number of nodes in the tree: ");
    scanf ("%d", &n);
    int *arr1 = (int *) malloc(sizeof(int)*n);
    printf("Enter the level-order data elements of the tree (positive ints separated by space):");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    
    Node r1 = makeTree(n, arr1);
    r1 = removeNullNodes(r1);


    // Enter the function calls to the code for the 
    // different questions for Assignment 2 below this line
    printf("Enter the number of nodes in the tree: ");
    scanf ("%d", &n);
    int *arr2 = (int *) malloc(sizeof(int)*n);
    printf("Enter the level-order data elements of the tree (positive ints separated by space):");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr2[i]);
    
    Node r2 = makeTree(n, arr2);
    r2 = removeNullNodes(r2);

    bool run = true; 
    int choice; 

    while (run)
    {
        printf("\nEnter a choice: \n"
            "[1] Structure Identical Check \n"
            "[2] Structure and Value Identical Check\n" 
            "[3] Exit \n"
        ); 
        /*Get choice from user*/
        scanf("%d", &choice );
        /*Switch to handle all different choices*/ 
        switch (choice)
        {
        case 1:
            printf("Are Trees structurally identical ? %s \n",
                    structurally_identical(r1,r2) ? "Yes" : "No"
            );
            break;
        case 2: 
            printf("Are trees completely identical ? %s \n",
                    are_identical(r1,r2) ? "Yes" : "No"
            ); 
            break; 
        case 3: 
            printf("Exiting program...\n"); 
            run = false; 
            break; 
        default:
            printf("Enter a valid value as choices \n"); 
            break;
        }
    }

    MakeEmpty(r1);
    MakeEmpty(r2);
}

/*
* Question 3        : A
* Function name     : structurally_identical
* Arguments         : T1,T2 = Node structure (pointer to the root of a binary tree)
* Return value/s    : ElementType (1 for true, 0 for false)
* Remarks           : Checks if two binary trees are completely identical (same structure and same node values)
*/
ElementType structurally_identical(Node T1, Node T2){
    /*If both trees are empty, the structure is the same*/
    if (T1 == NULL && T2 == NULL)
    {
        return 1; 
    }

    /*If one tree is empty and the other not, the structure is different*/
    if (T1 == NULL || T2 == NULL)
    {
        return 0; 
    }
    
    /*
    Check if current nodes have the same structure (both have or don't have left/right children)
    and recursively check if their subtrees are structurally identical
    */
    return structurally_identical(T1->Left, T2->Left) &&
           structurally_identical(T1->Right, T2->Right); 
}

/*
* Question 3        : B
* Function name     : are_identical
* Arguments         : T1,T2 = Node structure (pointer to the root of a binary tree)
* Return value/s    : ElementType (1 for true, 0 for false)
* Remarks           : Checks if two binary trees are completely identical (same structure and same node values)
*/
ElementType are_identical(Node T1,Node T2){ 
   /*If both trees are empty, they are identical*/
   if (T1 == NULL && T2 == NULL)
   {
       return 1; 
   }

   /*If one is empty and one is not, they are not identical*/
   if (T1 == NULL || T2 == NULL)
   {
        return 0; 
   }
   
   return(T1->Element == T2->Element) &&
         are_identical(T1->Left, T2->Left) && 
         are_identical(T1->Right, T2->Right);
}