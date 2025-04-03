/* 
* SAVA - 1B 
* Show the result of running Shellsort on the following
* input with the increment sequence {1, 3, 7}. At each step, you must show the array and record
* the number of swaps, as shown on the lecture slides.
* -46 73 10 -89 55 -32 28 91 -15 -79 64 -3 42 -68 7 -20 86 -95 49 -52
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType; 

/* Function prototype */
int countInversions(ElementType array[], ElementType size); 
void shellSort(ElementType array[], ElementType size, ElementType increments[], 
                ElementType numIncrements, int *countingSwap );
void printArray(ElementType array[], ElementType size); 

int main(){
    /* lolal vars */
    ElementType sizeArray; 
    ElementType *array;
    ElementType incrementSequence[] = {7,3,1}; 
    ElementType numIncrements = sizeof(incrementSequence) / sizeof(incrementSequence[0]); 
    int numberOfInversion, countingSwap = 0; 

    /* Ask and validate the size of the array */
    printf("Enter the number of element of the array : "); 
    while (scanf("%d", &sizeArray) != 1 || sizeArray < 1) {
        printf("Invalid input. Enter a positive integer: ");
        while (getchar() != '\n'); /* Clear input buffer */
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

    /* Count inversion calling countInversion() */
    numberOfInversion = countInversions(array,sizeArray);
    printf("Number of inversions : %d \n", numberOfInversion); 

    /* Show original array */
    printf("Original     : ");
    printArray(array,sizeArray); 
    
    /* Sort the array by calling shellSort() */
    shellSort(array,sizeArray,incrementSequence,numIncrements, &countingSwap); 

    /* Notify */
    printf("Total swap in shell sort --> %d \n", countingSwap); 
    printf("Number of swap saved --> %d \n", numberOfInversion - countingSwap); 

    free(array); 
    return 0; 
}

/* 
* Function name    : shellSort
* Arguments        : array[]                = (array of integers to be sorted)
*                    size                   = (integer representing the size of the array)
*                    increments[]           = (array of gap values for Shellsort)
*                    numIncrements          = (integer representing the number of increments)
*                    countingSwap           = (pointer to an integer to track the number of swaps)
* Return value/s   : None                   = (void function)
* Remarks          : Implements Shellsort using the provided increment sequence {1, 3, 7}
*                    The function iterates over each gap value, performing insertion sort for each.
*                    The number of swaps made during sorting is tracked via countingSwap.
*                    The array state is printed after each increment step.
*/
void shellSort(ElementType array[], ElementType size, ElementType increments[], 
    ElementType numIncrements, int *countingSwap ){
        /* First loop : to track the increment sequence {0...N} */
        for (int incId = 0; incId < numIncrements; incId++)
        {
            /* save gap value based on increments[index] */
            int gap = increments[incId]; 
            /* Second loop : */
            for (int i = gap; i < size; i++)
            {
                ElementType temp = array[i]; 
                int j;
                /* Third loop : compare and swap data */
                for (j = i; j>= gap && array[j-gap] > temp; j -= gap)
                {
                    /* swap data */
                    array[j] = array[j-gap];
                    (*countingSwap) ++;
                /* End of third loop */
                }                
                array[j] = temp;
            /* End of second loop */
            }
        /* Print array after each gap - tryi to follow lectures example */
        printf("After %d-sort : ", gap);
        printArray(array,size); 
        /* End of first loop */
        }
    } 

/* 
* Function name    : printArray
* Arguments        : array[]            = (array of integers)
*                    size               = (integer representing the size of the array)
* Return value/s   : None               = (void function)
* Remarks          : Prints the elements of the array in a single line separated by spaces.
*                    Used to display the array after each sorting step.
*/
void printArray(ElementType array[], ElementType size){

    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]); 
    }
    printf("\n");
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