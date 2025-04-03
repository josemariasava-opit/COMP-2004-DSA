/* 
* SAVA 5
* Write a program that reads N points in a plane and outputs any group of four or more collinear points 
* (i.e., points on the same line). The obvious brute-force algorithm requires O(N4) time. The program you 
* write should use any sorting algorithm and solve the problem in O(N2 log N) time. Your program should 
* not print groups of three or less collinear points. 
*/

/*
* slope calculation --> p2.y - p1.y / p2.x - p1.x  
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* 
* Struct to store the coordinates of the point x and y 
* index stores the point in the input list 
*/
typedef struct {
    int x;
    int y;
    int index;
} Point;

/* 
* Struct to store a point and its slope (dy/dx) respect to a reference point 
*/
typedef struct {
    Point point; /* reference point */
    int slope_dy;
    int slope_dx;
} Slope;

/* Function prototype */
int greatCommonDivisor(int x, int y); 
void calculateSlope(Point p1, Point p2, int *slope_dy, int *slope_dx); 
void merge(Slope *array, int left, int mid, int right); 
void mergeSort(Slope * array, int left, int right); 
void printPoint(Point p); 

int main(){
    /* local var */
    int sizeArray, result; 
    bool collinearFound; 

    /* Ask and validate the size of the array */
    printf("Enter the number of data points : "); 
    while (scanf("%d", &sizeArray) != 1 || sizeArray < 1) {
        printf("Invalid input. Enter a positive integer: ");
        while (getchar() != '\n'); /* Clear input buffer */
    }

    /* Allocate memory for the array of points */
    Point *pPointArray = malloc(sizeArray * sizeof(Point)); 
    if (!pPointArray)
    {   /* Notify */
        perror("Memory allocation failed for the array of points \n");
        return 1;
    }
    
    printf("Enter the data points in format (x, y): ");
    for (int i = 0; i < sizeArray; i++)
    {
        do
        {
            result = scanf(" (%d, %d)", &pPointArray[i].x, &pPointArray[i].y); 
            /* invalid input, not 2 number */
            if (result != 2 )
            {
                printf("Invalid format! point at index [%d] does not respect the format (x, y) \n",i);
                while (getchar() != '\n'); /* Clear input buffer */
            }
        } while (result != 2);
        /* Store original index */
        pPointArray[i].index = i; 
    /* end of for loop */
    }
    
    printf("\nCollinear points found: \n"); 
    collinearFound = false; 

    /* iterate through each point as a reference point*/
    for (int i = 0; i < sizeArray; i++)
    {
        Point pointReference = pPointArray[i]; 
        /* Allocate enough space for all points (maximum is sizeArray) */
        Slope *pSlopes = malloc(sizeArray * sizeof(Slope)); 
        if (!pSlopes) {
            perror("Memory allocation failed for slopes array\n");
            free(pPointArray);
            return 1;
        }
        
        int slopeCount = 0; 

        /* Calculate slope now - from reference point to all other points */
        for (int j = 0; j < sizeArray; j++)
        {
            // Skip the reference point itself
            if (j == i) continue;
            
            pSlopes[slopeCount].point = pPointArray[j]; 
            pSlopes[slopeCount].point.index = j; 
            calculateSlope(pointReference, pPointArray[j], &pSlopes[slopeCount].slope_dy, &pSlopes[slopeCount].slope_dx);
            slopeCount++; 
        }
        
        /* Sort points by slope calling mergeSort() */
        if (slopeCount > 0)
        {
            mergeSort(pSlopes, 0, slopeCount - 1); 
        }

        /* now - find groups of collinear points */
        int start = 0; 
        while (start < slopeCount)
        {
            int end = start + 1; 
            while (end < slopeCount && 
                   pSlopes[end].slope_dx == pSlopes[start].slope_dx &&
                   pSlopes[end].slope_dy == pSlopes[start].slope_dy)
            {
                end++; 
            }

            /* Check if we have 4 or more collinear points (including reference point) */
            if (end - start >= 3) // 3 points in slopes array + reference point = 4 points total
            {
                int printGroup = 1; 
                /* Check if this is the first occurrence of this line */
                for (int k = start; k < end; k++)
                {
                    if (pSlopes[k].point.index < i)
                    {
                        printGroup = 0; 
                        break; 
                    }
                }
                /* Print the group if it's the first occurrence */
                if (printGroup)
                {
                    collinearFound = true; 
                    printPoint(pointReference); 
                    for (int k = start; k < end; k++)
                    {
                        printf(" "); 
                        printPoint(pSlopes[k].point); 
                    }
                    printf("\n"); 
                }
            }
            start = end; 
        }
        free(pSlopes); 
    /* end of main for loop */
    }

    /* Notify if no collinear points group are present */
    if (!collinearFound)
    {
        printf("Cannot find groups of 4 or more collinear points \n"); 
    }

    /* free memory */
    free(pPointArray); 
    return 0; 
}
/* 
* Function name    : greatCommonDivisor
* Arguments        : a      = (integer value) 
*                    b      = (integer value)
* Return value/s   : int    = (greatest common divisor of a and b)
* Remarks          : Calculates the greatest common divisor using Euclidean algorithm.
*                    Used to reduce fractions to their simplest form, to store the point in simple way 
*                    and making comparison efficient. 
*/
int greatCommonDivisor(int a, int b){
    /* Calling abs() from math.h to return the absolute value of a number */
    a = abs(a); 
    b = abs(b); 
    while (b != 0)
    {
        int tmp = b;
        b = a % b; 
        a = tmp;  
    }
    return a; 
}

/* 
* Function name    : calculateSlope
* Arguments        : p1         = (Point structure of first point)
*                    p2         = (Point structure of second point)
*                    slope_dy   = (pointer to store the y of the slope - numerator)
*                    slope_dx   = (pointer to store the x of the slope - denominator)
* Return value/s   : None       = (void function)
* Remarks          : Calculates the slope between two points as a reduced fraction (dy/dx) 
*                    simplified values using greatCommonDivisor()
*                    Handles special cases for identical points and vertical lines.
*/
void calculateSlope(Point p1, Point p2, int *slope_dy, int *slope_dx){
    
    int dx = p2.x - p1.x; /* Horizontal difference */
    int dy = p2.y - p1.y; /* Vertical difference */ 
    /* Special case - points are the same*/
    if (dx == 0 && dy == 0)
    {
        *slope_dy = 0; /* slope is meaningless for identical points, set slope x-y = 0 */
        *slope_dx = 0; 
        return; 
    }
    /* 
    * Special case - vertical line where dx == 0
    * store the slope as (1,0) and not infinity 
    */
    if (dx == 0)
    {
        *slope_dy = 1; /* vertical line has undefined slope because dy/dx its a division by 0 */
        *slope_dx = 0; 
        return;         
    }
    /* calculate greatCommonDivisor and simplify the fraction */
    int gcdValue = greatCommonDivisor(dy, dx); 
    int simple_dy = dy / gcdValue; 
    int simple_dx = dx / gcdValue; 
    /* 
    * ensure that dx is a positive value 
    * if the dx value is negative, negate both to keep consistency 
    * and make simpler the comparison of collinear points. 
    */
    if (simple_dx < 0)
    {
        simple_dy = -simple_dy; 
        simple_dx = -simple_dx;
    }

    /* Store the slope in the output var */
    *slope_dy = simple_dy; 
    *slope_dx = simple_dx; 
}
/* 
* Function name    : merge
* Arguments        : array      = (array of Slope structures)
*                    left       = (starting index of the left subarray)
*                    mid        = (ending index of the left subarray)
*                    right      = (ending index of the right subarray)
* Return value/s   : None       = (void function)
* Remarks          : Merges two sorted subarrays into a single sorted array.
*                    Used as a helper function for mergeSort() 
*/
void merge(Slope *array, int left, int mid, int right){
    int i, j, k; 
    int n1 = mid - left + 1; /* Size of left subarray */
    int n2 = right - mid; /* Size of right subarray */

    /* Create temp arrays and allocate memory */
    Slope *lSubArray = malloc(n1 * sizeof(Slope)); 
    if (!lSubArray)
    {
        perror("Cannot allocate memory for subArray left \n"); 
        return; 
    }
    Slope *rSubArray = malloc(n2 * sizeof(Slope)); 
    if (!rSubArray)
    {
        perror("Cannot allocate memory for subArray right \n");
        free(lSubArray); 
        return; 
    }
    
    /* Copy the point and slope into subarrays */
    for (i = 0; i < n1; i++)
    {
        lSubArray[i] = array[left + i]; 
    }
    for (j = 0; j < n2; j++) // Fixed: was incorrectly incrementing i instead of j
    {
        rSubArray[j] = array[mid + 1 + j]; // Fixed: was using i instead of j
    }
    
    /* Merge back into original array */
    i = 0; /* index for lSubArray */
    j = 0; /* index for rSubArray */
    k = left; /* index for merged array */

    while (i < n1 && j < n2)
    {
        /* 
        * Compare slopes 
        * Sorting is based on slope (dx, dy) and, if slopes are equal, original index.
        */
        if ((lSubArray[i].slope_dx < rSubArray[j].slope_dx) || 
            (lSubArray[i].slope_dx == rSubArray[j].slope_dx && lSubArray[i].slope_dy < rSubArray[j].slope_dy) ||
            ((lSubArray[i].slope_dx == rSubArray[j].slope_dx && lSubArray[i].slope_dy == rSubArray[j].slope_dy) && 
             (lSubArray[i].point.index < rSubArray[j].point.index))) // Fixed: missing parenthesis
        {
            array[k] = lSubArray[i]; 
            i++; 
        }
        else
        {
            array[k] = rSubArray[j]; 
            j++; 
        }
        k++; 
    }
    /* 
    * If one subarray still has Slope elements left, they are copied back to original array 
    * merge sort works recursively, the two subarrays being merged might have different sizes.
    */
    /* copy remaining element from left sub array */
    while (i < n1)
    {
        array[k] = lSubArray[i]; 
        i++; 
        k++; 
    }
    /* copy remaining element from right sub array */
    while (j < n2) // Fixed: was j <n2 (space missing)
    {
        array[k] = rSubArray[j]; 
        j++; 
        k++; 
    }
    
    /* Free allocated memory after finish with sub arrays */
    free(lSubArray); 
    free(rSubArray); 
}
/* 
* Function name    : mergeSort
* Arguments        : array      = (array of Slope structures)
*                    left       = (starting index of the array)
*                    right      = (ending index of the array)
* Return value/s   : None       = (void function)
* Remarks          : Sorts an array of Slope structures using the merge sort algorithm.
*                    Sorts primarily by slope, then by original index if slopes are equal.
*/
void mergeSort(Slope *array, int left, int right) {
    
    if (left < right) {
        int mid = left + (right - left) / 2; /* find middle index */
        
        /* Step 1 : recursively sort the left half */
        mergeSort(array, left, mid);
        /* Step 2 : recursively sort the right half */
        mergeSort(array, mid + 1, right);
        /* Step 3 : call merge() and merge the two parts */
        merge(array, left, mid, right);
    }
}

/* 
* Function name    : printPoint
* Arguments        : p      = (Point structure)
* Return value/s   : None   = (void function)
* Remarks          : Prints a single point in the format (x, y).
*/
void printPoint(Point p){
    printf("(%d, %d)", p.x, p.y); 
}