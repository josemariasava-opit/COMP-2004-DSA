#include <stdio.h>
#include <stdlib.h>

int main(){
    int num_rows = 3, num_cols = 4;
    
    int **arr2d;
    // first allocate memory num_rows pointers 
    arr2d = (int **)malloc(num_rows*sizeof(int*));

    // then allocate memory for num_cols elements for each row
    for (int i = 0; i < num_cols; i++)
        arr2d[i] = (int *)malloc(num_cols*sizeof(int));
        
    // Enter the data from console to initialize 'arr2d'
    printf("Enter the data for the 2-d array\n");
    for (int r = 0; r < num_rows; r++){
        for (int c = 0; c < num_cols; c++){
            printf("Enter item at [%d][%d]: ", r, c);
            scanf("%d", arr2d[r]+c);
        }
    }
    
    // Print elements of 'arr2d'
    for (int r = 0; r < num_rows; r++){
        for (int c = 0; c < num_cols; c++)
            printf("Element at [%d][%d]: %d\n", r, c, arr2d[r][c]);
    }
}