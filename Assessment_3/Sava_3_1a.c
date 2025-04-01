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

    /* Free the memory allocated for the array */
    free(array);     
    return 0; 
}

/* 
* Function name    : countInversions
* Arguments        : array[]            = (array of integers), 
                     size               = (integer representing the size of the array)
* Return value/s   : ElementType        = (integer representing the number of inversions in the array)
* Remarks          : Counts the number of inversions in the input array.
*                    An inversion is a pair (i, j) where i < j and array[i] > array[j].
*                    Returns the total number of such inversions.
*/
int countInversions(ElementType array[], ElementType size){
    int numberInversions = 0; 
    for (int p = 0; p < size - 1; p++)
    {
        for (int j = p+1 ; j < size; j++)
        {
            if (array[p] > array[j])
            {
                numberInversions ++; 
            }
        }
    }
    return numberInversions;    
}