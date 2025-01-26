/* 
Exercise: Write a program to demonstrate the difference between an array and a pointer.

    Goal: Learn that an array name is a pointer to the first element, but they are not the same in all contexts.
    Hint: Compare the two in different scenarios, like passing them to functions.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){

    int array[] = {2,4,7,8}; 

    int *pArray = NULL; 

    pArray = array; // Array name is a pointer to the first element

    printf("Array[0] = %d\n", array[0]);

    printf("Pointer to Array = %d\n", *pArray);


    return 0; 
}