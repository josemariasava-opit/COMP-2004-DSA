#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Question 4 : Main program
* Function name : main
* Arguments : none
* Return value/s : int (program exit status)
* Remarks : Menu-driven interface to test BST functions
*/
int main() {
    SearchTree T = NULL;
    int choice, element, k;
    ElementType* levelOrderResult;
    Position kthMin;
    int nodeCount = 0;
    
    while (1) {
        printf("\nEnter a choice:\n"
            "[1] Insert (individual node)\n"
            "[2] Bulk Insert (from array)\n"
            "[3] findMin_K\n"
            "[4] numLeafNodes\n"
            "[5] LevelOrder\n"
            "[6] PrintTree (in-order)\n"
            "[7] Exit\n"
        );
        /*Get choice from user*/
        scanf("%d", &choice);
        
        /*Switch to handle all different choices*/ 
        switch(choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                T = Insert(element, T);
                printf("Element %d inserted.\n", element);
                break;
                
            case 2: {
                int size, i;
                printf("Enter number of elements to insert: ");
                scanf("%d", &size);
                
                int* elements = (int*)malloc(size * sizeof(int));
                if (elements == NULL) {
                    printf("Memory allocation failed!\n");
                    break;
                }
                
                printf("Enter %d elements separated by spaces: ", size);
                for (i = 0; i < size; i++) {
                    scanf("%d", &elements[i]);
                }
                
                /* Insert all elements from array*/
                for (i = 0; i < size; i++) {
                    T = Insert(elements[i], T);
                }
                
                printf("%d elements inserted successfully.\n", size);
                free(elements);
                break;
            }
                
            case 3:
                printf("Enter value of k: ");
                scanf("%d", &k);
                
                /* Reset static variables before new search*/
                findMin_K(NULL, -1);
                
                kthMin = findMin_K(T, k);
                if (kthMin != NULL)
                    printf("The %dth smallest element is: %d\n", k, Retrieve(kthMin));
                else
                    printf("No %dth smallest element found (k may be too large)\n", k);
                break;
                
            case 4:
                printf("Number of leaf nodes: %d\n", numLeafNodes(T));
                break;
                
            case 5:
                printf("Performing levelOrder() function ...\n"); 
                levelOrder(T);
                break;
                
            case 6:
                printf("In-order traversal: ");
                PrintTree(T);
                printf("\n");
                break;
                
            case 7:
                printf("Exiting program...\n");
                MakeEmpty(T);  /* Free all allocated memory*/
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}