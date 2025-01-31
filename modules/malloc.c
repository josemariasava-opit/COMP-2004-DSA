#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    
    int *arr = (int *)malloc(n*sizeof(int));
    // memory 'arr' allocated but not initialized
 
    printf("Enter %d integers separated by a single space: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", arr+i); // initialize each element of 'arr'
        
        
    for (int i = 0; i < n; i++)
        printf("arr[%d] = %d\n", i, *(arr+i));  //print elements of 'arr'
        
    free(arr); // release memory allocated for 'arr' by malloc
    printf("After doing free, array memory is released and array data points to garbage...\n");
    printf("arr[0] = %d\n", *arr);
}