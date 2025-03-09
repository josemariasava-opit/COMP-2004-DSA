#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

struct TreeNode
{
    ElementType Element;
    SearchTree  Left;
    SearchTree  Right;
};


SearchTree
MakeEmpty( SearchTree T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

Position
Find( ElementType X, SearchTree T )
{
    if( T == NULL )
        return NULL;
    if( X < T->Element )
        return Find( X, T->Left );
    else
    if( X > T->Element )
        return Find( X, T->Right );
    else
        return T;
}

Position
FindMin( SearchTree T )
{
    if( T == NULL )
        return NULL;
    else
    if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

Position
FindMax( SearchTree T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

SearchTree
Insert( ElementType X, SearchTree T )
{
/* 1*/      if( T == NULL )
    {
        /* Create and return a one-node tree */
/* 2*/          T = malloc( sizeof( struct TreeNode ) );
/* 3*/          if( T == NULL )
        {
/* 4*/              printf( "Out of space!!!" );
            exit(1);
        }
        else
        {
/* 5*/              T->Element = X;
/* 6*/              T->Left = T->Right = NULL;
        }
    }
    else
/* 7*/      if( X < T->Element )
/* 8*/          T->Left = Insert( X, T->Left );
    else
/* 9*/      if( X > T->Element )
/*10*/          T->Right = Insert( X, T->Right );
    /* Else X is in the tree already; we'll do nothing */

/*11*/      return T;  /* Do not forget this line!! */
}

SearchTree
Delete( ElementType X, SearchTree T )
{
    Position TmpCell;

    if( T == NULL )
    {
        printf( "Out of space!!!" );
        exit(1);
    }
    else
    if( X < T->Element )  /* Go left */
        T->Left = Delete( X, T->Left );
    else
    if( X > T->Element )  /* Go right */
        T->Right = Delete( X, T->Right );
    else  /* Found element to be deleted */
    if( T->Left && T->Right )  /* Two children */
    {
        /* Replace with smallest in right subtree */
        TmpCell = FindMin( T->Right );
        T->Element = TmpCell->Element;
        T->Right = Delete( T->Element, T->Right );
    }
    else  /* One or zero children */
    {
        TmpCell = T;
        if( T->Left == NULL ) /* Also handles 0 children */
            T = T->Right;
        else if( T->Right == NULL )
            T = T->Left;
        free( TmpCell );
    }

    return T;
}


ElementType
Retrieve( Position P )
{
    return P->Element;
}

void PrintTree(SearchTree T)
{
    if ( T!= NULL )
    {
        PrintTree(T->Left);
        printf("%d ", T->Element);
        PrintTree(T->Right);    }
}

/*Sava question 4 */

/*
* Question 4        : A
* Function name     : findMin_K
* Arguments         : T = Node structure (pointer to the root of a binary tree)
*                     k = integer value representing the kth smallest element to find
* Return value/s    : Position pointer to the kth smallest node
* Remarks           : Uses in-order traversal to find the kth smallest element in the BST
*/
Position findMin_K(SearchTree T, ElementType k){
    if (T == NULL || k <= 0)
    {
        return NULL;
    }

    ElementType nodeCount = 0; 
    SearchTree temp = T; 
    countNodes(temp, &nodeCount); 

    /* Use to simulate the stack*/
    SearchTree array[nodeCount]; 

    ElementType top = -1; 

    SearchTree currentNode = T; 
    int counter = 0; 

    while (currentNode != NULL || top >= 0)
    {
        /*Go to the Left*/
        while (currentNode != NULL)
        {
            array[++top] = currentNode; 
            currentNode = currentNode->Left;
        }
        
        currentNode = array[top--]; 
        counter ++; 

        if (counter == k)
        {
            return currentNode; 
        }

        /* Move to the right*/
        currentNode = currentNode->Right; 
    }
    /*if k value is greater than the number on nodes*/
    return NULL; 
}


/*
* Question 4        : B
* Function name     : numLeafNodes
* Arguments         : T = Node structure (pointer to the root of a binary tree)
* Return value/s    : ElementType total count of leaf node
* Remarks           : Counts the number of leaf nodes (nodes with no children) in the BST
*/
ElementType numLeafNodes(SearchTree T){
    /*First case : empty tree*/
    if (T == NULL)
    {
        return 0; 
    }
    
    /* Is a leaf node ?*/
    if (T->Left == NULL && T->Right == NULL)
    {
        return 1; 
    }

    return numLeafNodes(T->Left) + numLeafNodes(T->Right);
}

/*
* Question 4        : C 
* Function name     : numLeafNodes
* Arguments         : T = Node structure (pointer to the root of a binary tree)
* Return value/s    : ElementType* array of elements in level order
* Remarks           : Traverses the BST in level order (breadth-first) and returns an array of elements
*/
ElementType* levelOrder(SearchTree T){
    if (T == NULL)
    {
        printf("Empty Tree \n");
        return NULL; 
    }

    /*Count number of nodes to allocate correctly the array size*/
    ElementType nodeCount = 0; 
    countNodes(T, &nodeCount); 

    /*Allocate memory for queue*/
    SearchTree* queue = malloc(nodeCount * sizeof(SearchTree)); 
    if (queue == NULL)
    {
        printf("Memory allocation failed"); 
        exit(1); 
    }

    ElementType front = 0; 
    ElementType rear = 0; 

    queue[rear++] = T; 

    printf("Level order traversal: "); 

    while (front < rear)
    {
        SearchTree current = queue[front++]; 

        printf("%d ", current->Element); 

        /*Left child if exist*/
        if (current->Left != NULL)
        {
            queue[rear++] = current->Left; 
        }

        /*Right child if exist*/
        if (current->Right != NULL)
        {
            queue[rear++] = current->Right; 
        }
    }

    printf("\n");
    free(queue); 
}

/*
* Question 4        : Counter helper 
* Function name     : countNodes
* Arguments         : T = Node structure (pointer to the root of a binary tree)
*                     count = pointer to integer to store the node count
* Return value/s    : void (updates count via pointer)
* Remarks           : Counts the total number of nodes in a binary tree
*/
void countNodes(SearchTree T, ElementType* counter){
    if (T != NULL)
    {
        (*counter) ++; 
        countNodes(T->Left, counter); 
        countNodes(T->Right, counter); 
    }
}