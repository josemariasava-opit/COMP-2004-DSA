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

/* Function prototypes */
int greatCommonDivisor(int x, int y);
void calculateSlope(Point p1, Point p2, int *slope_dy, int *slope_dx);
void printPoint(Point p);

/* Import functions from sort.c */
void Merge(Slope A[], Slope TmpArray[], int Lpos, int Rpos, int RightEnd);
void MSort(Slope A[], Slope TmpArray[], int Left, int Right);
void MergeSort(Slope A[], int N);

/* Compare function for Slopes to be used with sorting algorithms */
int compareSlopes(const Slope *a, const Slope *b);

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
            /* Skip the reference point itself */
            if (j == i) continue;
            
            pSlopes[slopeCount].point = pPointArray[j]; 
            pSlopes[slopeCount].point.index = j; 
            calculateSlope(pointReference, pPointArray[j], &pSlopes[slopeCount].slope_dy, &pSlopes[slopeCount].slope_dx);
            slopeCount++; 
        }
        
        /* Sort points by slope using MergeSort from sort.c */
        if (slopeCount > 0)
        {
            MergeSort(pSlopes, slopeCount);
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
            if (end - start >= 3) /* 3 points in slopes array + reference point = 4 points total */ 
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
* Function name    : printPoint
* Arguments        : p      = (Point structure)
* Return value/s   : None   = (void function)
* Remarks          : Prints a single point in the format (x, y).
*/
void printPoint(Point p){
    printf("(%d, %d)", p.x, p.y); 
}

/* 
* Function name    : compareSlopes
* Arguments        : a     = (pointer to Slope structure)
*                    b     = (pointer to Slope structure)
* Return value/s   : int   = (-1 if a < b, 0 if a == b, 1 if a > b)
* Remarks          : Compare function for Slopes to be used with sorting algorithms.
*                    Compares slopes first, then original indices if slopes are equal.
*/
int compareSlopes(const Slope *a, const Slope *b) {
    if (a->slope_dx < b->slope_dx) {
        return -1;
    } else if (a->slope_dx > b->slope_dx) {
        return 1;
    } else {
        if (a->slope_dy < b->slope_dy) {
            return -1;
        } else if (a->slope_dy > b->slope_dy) {
            return 1;
        } else {
            if (a->point.index < b->point.index) {
                return -1;
            } else if (a->point.index > b->point.index) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

/* 
* Adapted functions from sort.c to work with Slope structures 
*/

void
Merge(Slope A[], Slope TmpArray[], int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, NumElements, TmpPos;

    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while (Lpos <= LeftEnd && Rpos <= RightEnd) {
        if (compareSlopes(&A[Lpos], &A[Rpos]) <= 0)
            TmpArray[TmpPos++] = A[Lpos++];
        else
            TmpArray[TmpPos++] = A[Rpos++];
    }

    while (Lpos <= LeftEnd)  /* Copy rest of first half */
        TmpArray[TmpPos++] = A[Lpos++];
    while (Rpos <= RightEnd) /* Copy rest of second half */
        TmpArray[TmpPos++] = A[Rpos++];

    /* Copy TmpArray back */
    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpArray[RightEnd];
}

void
MSort(Slope A[], Slope TmpArray[], int Left, int Right)
{
    int Center;

    if (Left < Right) {
        Center = (Left + Right) / 2;
        MSort(A, TmpArray, Left, Center);
        MSort(A, TmpArray, Center + 1, Right);
        Merge(A, TmpArray, Left, Center + 1, Right);
    }
}

void
MergeSort(Slope A[], int N)
{
    Slope *TmpArray;

    TmpArray = malloc(N * sizeof(Slope));
    if (TmpArray != NULL) {
        MSort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    } else {
        printf("No space for tmp array!!!\n");
        exit(1);
    }
}