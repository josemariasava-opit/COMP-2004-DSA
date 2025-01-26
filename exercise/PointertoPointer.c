/* 
Exercise: Write a program that demonstrates the use of a pointer to a pointer.

    Goal: Understand how multi-level pointers work and when they are useful (like for dynamically allocated arrays or passing pointers to functions).
    Hint: Create a pointer that points to another pointer, and dereference it twice.

*/

#include <stdio.h>

int main(void){ 

    int a = 1; 

    int *pA = NULL; 

    pA = &a; 

    int **pA2 = &pA; 

    printf("Value of pointer n.2 = %d \n", **pA2);

    printf("Memory address of pointer *pA = %p \n", (void *)&pA); 
    printf("Memory address of pointer *pA2 = %p \n", (void *)&pA2); 




    return 0; 
}