/*
Exercise: Write a program that uses pointer arithmetic to access elements of an array.

    Goal: Learn how pointers and array indexing are closely related in C. Understand how pointer arithmetic works for arrays.
    Hint: Use pointer increments (ptr++) to traverse through an array.
*/

#include <stdio.h>

int main(){

    // init array 

    int array[] = {10,20,30,40,50}; 

    int *pArray = array; // pointer to array 

    for(int i= 0; i<5; i++){

        printf("Value at index [%d] is : %d \n", i, *(pArray+i));
    } 


}