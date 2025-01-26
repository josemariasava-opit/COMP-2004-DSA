/*
Exercise: Write a program that declares a variable, assigns a value to it, and then prints the value both directly and via a pointer.

    Goal: Understand how to use the address-of operator (&) and dereference operator (*).
    Hint: Use the address of a variable and store it in a pointer. Then, dereference the pointer to get the value back.
*/

#include <stdio.h>

int main(void){

    int value = 10; 
    int *pValue = NULL;     

    pValue = &value; 

    printf("This is the value of var : %d\n", value);

    printf("This is the value of pointer to var : %d \n", *pValue);


}