#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_from_list.c"
#include <stdbool.h>

/*Function prototypes*/
ElementType count_nodes(Node T); 
ElementType sum_keys(Node T); 
ElementType max_key(Node T); 
void print_below(Node T, ElementType v); 

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
    // Menu-driven interface
    int choice = 0;
    ElementType result, v;
    bool run = true; 
    
    while (run) {
        printf("\nEnter a choice:\n"
            "[1] Count Nodes\n"
            "[2] Sum Keys\n"
            "[3] Max Key\n"
            "[4] Print Below\n"
            "[5] Exit\n"
        );
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                result = count_nodes(r);
                printf("Number of nodes in the tree: %d\n", result);
                break;
                
            case 2:
                result = sum_keys(r);
                printf("Sum of all keys in the tree: %d\n", result);
                break;
                
            case 3:
                result = max_key(r);
                if (result == -1)
                    printf("Tree is empty\n");
                else
                    printf("Maximum key in the tree: %d\n", result);
                break;
                
            case 4:
                printf("Enter the value v: ");
                scanf("%d", &v);
                printf("Keys less than %d: ", v);
                print_below(r, v);
                printf("\n");
                break;
                
            case 5:
                printf("Exiting program...\n");
                run = false; 
                break;
                
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    free(arr); 
    MakeEmpty(r);
}


/*
 * Question 1       : A
 * Function name    : count_nodes
 * Arguments        : T = Node structure (pointer to the root of a binary tree)
 * Return value/s   : ElementType (integer representing the number of nodes in the binary tree)
 * Remarks          : Recursively counts the number of nodes in the binary tree
 *                    Return 0 if the tree is empty
 */
ElementType count_nodes(Node T) {
    /*Base case: if the node is NULL, return 0*/
    if (T == NULL)
        return 0;
    
    /*Recursively count nodes in left subtree, right subtree, and add 1 for current node*/
    return 1 + count_nodes(T->Left) + count_nodes(T->Right);
}


/*
 * Question 1       : B
 * Function name    : sum_keys
 * Arguments        : T = Node structure (pointer to the root of a binary tree)
 * Return value/s   : ElementType (integer representing the sum of all keys in the binary tree)
 * Remarks          : Recursively calculates the sum of all keys in the binary tree
 *                    Return 0 if the tree is empty
 */
ElementType sum_keys(Node T) {
    /* Base case: if the node is NULL, return 0*/
    if (T == NULL)
        return 0;
    
    /* Return the sum of current node's value and values in left and right subtrees*/
    return T->Element + sum_keys(T->Left) + sum_keys(T->Right);
}

/*
 * Question 1       : C
 * Function name    : max_key
 * Arguments        : T = Node structure (pointer to the root of a binary tree)
 * Return value/s   : ElementType (integer representing the maximum key value in the binary tree)
 * Remarks          : Recursively finds the maximum key value in the binary tree
 *                    Return -1 if the tree is empty
 */
ElementType max_key(Node T) {
    /* Base case: if the node is NULL, return -1 (tree is empty)*/
    if (T == NULL)
        return -1;
    
    /* Get maximum values from left and right subtrees*/
    ElementType left_max = max_key(T->Left);
    ElementType right_max = max_key(T->Right);
    
    /* Find the maximum among current node, left subtree max, and right subtree max*/
    ElementType max = T->Element;
    
    /* Check if left subtree has a greater value (and is not empty)*/
    if (left_max != -1 && left_max > max)
        max = left_max;
    
    /* Check if right subtree has a greater value (and is not empty)*/
    if (right_max != -1 && right_max > max)
        max = right_max;
    
    return max;
}

/*
 * Question 1       : D
 * Function name    : print_below
 * Arguments        : T = Node structure (pointer to the root of a binary tree), 
 *                    v = ElementType (value to be checked)
 * Return value/s   : void (no return value)
 * Remarks          : Recursively prints all keys in the binary tree that are less than the value v
 *                    Performs an in-order traversal to print values in ascending order
 */
void print_below(Node T, ElementType v) {
    /* Base case: if the node is NULL, return*/
    if (T == NULL)
        return;
    
    /* In-order traversal: left subtree, current node, right subtree*/
    
    /* First process left subtree*/
    print_below(T->Left, v);
    
    /* Then check current node*/
    if (T->Element < v)
        printf("%d ", T->Element);
    
    /* Finally process right subtree*/
    print_below(T->Right, v);
}