/* 
Exercise: Write a program that dynamically allocates memory for an array using malloc and then frees it using free.

    Goal: Learn how to manage memory using pointers and avoid memory leaks.
    Hint: Allocate an array dynamically and access its elements via pointer arithmetic.

*/
#include <stdio.h> 
#include <stdlib.h>

int main(void){ 

    int size = 5;
    int *pArray = NULL; // initialize pointer to NULL to use it in the code 

    // Dynamic allocate with malloc() 
    pArray = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        *(pArray+i)= i * 5; 
        printf("Element[%d] : %d \n", i, *(pArray+i));
    }


    // free memory allocation 
    free(pArray);


    return 0; 
}