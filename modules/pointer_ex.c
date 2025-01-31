#include <stdio.h>


int main(void){ 
    // Pointer declaration type *pointerName

    int i = 50; 
    // is a pointer to an int
    int *pPtr = NULL; // initialize the pointer to NULL 
    int *pPtr2 = &i; // pPtr2 points to the memory address of int i


    printf("Value of i = %d \n", i);
    // printf("Address of i = %p \n", i);

    printf("Value of pPtr2 = %d \n", *pPtr2);
    printf("Address of pPtr2 = %p \n", pPtr2);

    return 0; 
}