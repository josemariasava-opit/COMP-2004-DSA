/*
a) The height of a tree is the maximum number of edges on a path from the root to a leaf node. 
Write a C function int height(BinaryTree T) that returns the height of a binary tree. 
b) The cost of a path in a tree is sum of the keys of the nodes participating in that path. Write a C 
function int path_cost(BinaryTree T) that returns the cost of the most expensive 
path from the root to a leaf node
*/

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_from_list.c"
#include <stdbool.h>

/*Function prototypes*/
ElementType height(Node T);
ElementType path_cost(Node T); 

int main()
{   
    int n;
    printf("Enter the number of nodes in the tree: ");
    scanf ("%d", &n);
    int *arr = (int *) malloc(sizeof(int)*n);
    printf("Enter the level-order data elements of the tree (positive ints separated by space):");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    Node r = makeTree(n, arr);
    r = removeNullNodes(r);

    printf("Inorder traversal: ");
    PrintTree(r);
    printf("\n");

    // Enter the function calls to the code for the 
    // different questions for Assignment 2 below this line
    bool run = true; 
    int choice; 

    while (run)
    {
        printf("\nEnter a choice: \n"
            "[1] Tree height\n"
            "[2] Max Path cost\n" 
            "[3] Exit \n"
        ); 
        /*Get choice from user*/
        scanf("%d", &choice );
        /*Switch to handle all different choices*/ 
        switch (choice)
        {
        case 1:
            printf("Tree Height : %d \n", height(r));
            break;
        case 2: 
            printf("Max Path cost : %d \n", path_cost(r)); 
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

    MakeEmpty(r);
}

/*
* Question 2        : A
* Function name     : height
* Arguments         : T = Node structure (pointer to the root of a binary tree)
* Return value/s    : ElementType (integer representing the height of the binary tree)
* Remarks           : Calculates the maximum number of edges from the root to any leaf node
*                     Return the maximum height plus 1 (for the edge connecting this node)
*/
ElementType height(Node T){
    if (T == NULL)
    {
        return -1; /*0 edges */
    }
    ElementType leftHeight = height(T->Left); 
    ElementType rightEight = height(T->Right);

    return(leftHeight > rightEight ? leftHeight : rightEight) +1; 
}

/*
* Question 2        : B
* Function name     : path_cost
* Arguments         : T = Node structure (pointer to the root of a binary tree)
* Return value/s    : ElementType (integer representing the most expensive path from root to leaf)
* Remarks           : Calculates the sum of node values along the path with maximum cost
*/
ElementType path_cost(Node T){
    if (T == NULL)
    {
        return 0; 
    }

    /*Check if it is a leaf node*/
    if (T->Left == NULL && T->Right == NULL)
    {
        return T->Element; 
    }

    ElementType leftCost = path_cost(T->Left);
    ElementType rightCost = path_cost(T->Right); 

    if (T->Left == NULL)
    {
        return T->Element + rightCost; 
    }
    if (T->Right == NULL)
    {
        return T->Element + leftCost; 
    }
    
    /*Take more expensive path*/
    return T->Element +(leftCost > rightCost ? leftCost : rightCost);
}