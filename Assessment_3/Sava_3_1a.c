/* 1 - A 
* Write a program that counts the number of inversions in an input array of integers. Your
* program should prompt the user to enter the number of elements in the input array and then the array elements. 
* It should then print the number of inversions in the input array.
* A sampleinput is shown below:
* Enter the number of elements in input array: 15
* Enter the array elements: -35 11 42 -7 -18 30 -44 23 -25 -6 9 -19 50 -49 38 
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType; 

/* Function prototypes */
int countInversions(ElementType array[], ElementType size); 

int main(){
    /* local vars */
    ElementType sizeArray; 
    ElementType *array;
    int numberOfInversion = 0; 

    /* Ask and validate the size of the array */
    printf("Enter the number of element of the array : "); 
    while (scanf("%d", &sizeArray) != 1 || sizeArray < 1) {
        printf("Invalid input. Enter a positive integer: ");
        while (getchar() != '\n'); /* Clean input buffer */
    }
    
    /* Allocate memory for the array */
    array = malloc(sizeArray*sizeof(int));
    /* Verify correct memory allocation */
    if (!array)
    {
        perror("Memory allocation failed for the array. \n"); 
        return 1; 
    }


    /* Ask the user to input the element of the array  */
    printf("Enter %d integers:\n", sizeArray);
    for (int i = 0; i < sizeArray; i++) {
        if (scanf("%d", &array[i]) != 1) {
            printf("Error: Invalid input for array element.\n");
            free(array); /*Free the allocated memory*/
            return 1;   /* Exit */
        }
    }

    /* Call countInversions() and store value */
    numberOfInversion = countInversions(array,sizeArray); 

    printf("Number of inversions --> %d", numberOfInversion); 

    printf("\nSorted Array  : \n"); 
    for (int i = 0; i < sizeArray; i++)
    {
        printf("%d ", array[i]); 
    }
    printf("\n");
    

    /* Free the memory allocated for the array */
    free(array);     
    return 0; 
}


int countInversions(ElementType array[], ElementType size){

    /* return var */
    int inversionsNumber = 0; 

    /* indexes of for loop*/
    ElementType j,p; 
    ElementType key; 

    for ( p = 1; p < size; p++)
    {
        /* temp is our key value*/
        key = array[p]; 
        for (j  = p; j> 0 && array[j-1]> key; j--)
        {
            array[j] = array[j-1]; 
            printf("Inversion found: [%d, %d]\n", array[j], key); 
            inversionsNumber ++; 
            /* End of j index second loop */
        }
        array[j] = key; 
        /* End of p index second loop */
    }
    /* Return value */
    return inversionsNumber; 
}