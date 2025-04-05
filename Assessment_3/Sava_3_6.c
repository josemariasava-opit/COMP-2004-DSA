#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.c" /* include sort.c */

/* Function prototype */
void subsetsFinder(int sortedValues[], int indexArray[], int n, int k, int index, 
                     int subset[], int subsetSize, int currentSum, bool *found); 
void inputParser(int arr[], int n);

int main() {
    int size, k;

    /* Ask and validate the size of the array */
    printf("Enter the number of data points : "); 
    while (scanf("%d", &size) != 1 || size < 1) {
        printf("Invalid input. Enter a positive integer: ");
        while (getchar() != '\n'); /* Clear input buffer */
    }
    getchar(); 
    
    int originalArray[size], sortedValues[size], indexArray[size];
    printf("Enter the array elements (separated by space or comma): ");
    inputParser(originalArray, size);
    
    /* Create a copy  of the array for sorting ( to store original index )*/
    memcpy(sortedValues, originalArray, size * sizeof(int));
    Bubblesort(sortedValues, size); /* Call Bubblesort from sort.c */
    
    /* Maps sorted values back to original index and stores in originalArray[]*/
    int usedArray[size]; /* Helps to avoids duplicate mapping */
    /* Memset() initialize the usedArray with zeros, setting each element at zero 
    ensure that no elements are considered "used"*/
    memset(usedArray, 0, sizeof(usedArray));
    /* Loop through sorted values array */
    for (int i = 0; i < size; i++) {
        /* Search in originalArray */
        for (int j = 0; j < size; j++) {
            /* 
            * If sortedValues[i] matches originalArray[j] AND 
            * originalArray[j] hasn't been used yet,
            * record the original index (j) in indexArray[i].
            */
            if (sortedValues[i] == originalArray[j] && !usedArray[j]) {
                indexArray[i] = j;/* store original index */
                usedArray[j] = 1; /* mark as used */
                break; /* Move to next item in sortedArray */
            }
            /* end of second loop */
        }
        /* end of first loop */
    }
    
    /* Ask user to input the target sum -- value k */
    printf("Enter the target sum (k): ");
    scanf("%d", &k);
    
    /* 
    * Edge case - if k is equal to zero. If found a zero print it and the index. 
    * If the 0 is not present, pints fail message. 
    */
    if (k == 0) {
        bool zeroValue = false;
        for (int i = 0; i < size; i++) {
            if (sortedValues[i] == 0) {
                zeroValue = true;
                printf("Output: Success!\n");
                printf("a[%d] = 0\n", indexArray[i]);
                printf("Sum = 0\n\n");
            }
        }
        printf(!zeroValue ? "Output: Fail!\n" : "");
        return 0;
    }
    
    int subset[size]; /* temp buffer to hold index during recursion of subsetsFinder()*/
    bool found = false;
    /* calling subsetsFinder to find combinations that sum to k*/
    subsetsFinder(sortedValues, indexArray, size, k, 0, subset, 0, 0, &found);
    
    /* Notify if subsets are not present */
    printf(!found ? "Output: Fail!\n" : "");
    return 0;
}

/* 
* Function name    : inputParser
* Arguments        : array[]    = (Array iof integer) 
*                    n          = (integer value) 

/* 
* Function name    : subsetsFinder 
* Arguments        : sortedValues[]    = (integer array) Sorted input values
*                    indexArray[]      = (integer array) Original positions of sorted values
*                    n                 = (integer) Size of array
*                    k                 = (integer) Target sum
*                    index             = (integer) Current position in recursion
*                    subset[]          = (integer array) Current subset being built
*                    subsetSize        = (integer) Size of current subset
*                    currentSum        = (integer) Accumulated sum of current subset
*                    found             = (bool pointer) Flag to indicate if any subset was found
* Return value/s   : void
* Remarks          : Recursive function using backtracking to find all subsets that sum to k value.
*                    Skips zeros when K ≠ 0 to avoid trivial solutions. Maintains original indices
*                    from unsorted array for the output to user 
*/
void subsetsFinder(int sortedValues[], int indexArray[], int n, int k, int index, 
                    int subset[], int subsetSize, int currentSum, bool *found) {

        /* If the current subset matches target sum k, prints the subset and exits recursion. */    
        if (currentSum == k && subsetSize > 0) {
        *found = true;
        printf("Output: Success!\n");
        for (int i = 0; i < subsetSize; i++) {
            int index = subset[i];
            printf("a[%d] = %d\n", indexArray[index], sortedValues[index]);
        }
        
        printf("Sum = %d\n\n", k);
        return;
        }
        /* Recursion case */
        for (int i = index; i < n; i++) {            
            if (sortedValues[i] == 0 && k != 0) continue; /* skip zero value - does not count */
            if (currentSum + sortedValues[i] <= k) {
                subset[subsetSize] = i;
                subsetsFinder(sortedValues, indexArray, n, k, i + 1, subset, subsetSize + 1, currentSum + sortedValues[i], found);
            }
        }
}

/* 
* Function name    : inputParser
* Arguments        : array[]    = (Array iof integer) 
*                    n          = (integer value) 
* Return value/s   : None       = (void function)
* Remarks          : Reads input line and parses integers separated by spaces/commas.
*                    Handles mixed delimiters and validates correct element count.
*                    Uses strtok for efficient tokenization of input string.
*/
void inputParser(int array[], int n) {
    char input[1024];
    fgets(input, sizeof(input), stdin);
    char *token = strtok(input, " ,");
    for (int i = 0; i < n && token != NULL; i++) {
        array[i] = atoi(token);
        token = strtok(NULL, " ,");
    }
}