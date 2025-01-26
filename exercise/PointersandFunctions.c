/*
Exercise: Write a function that accepts a pointer to a variable and modifies its value.

    Goal: Understand how passing by reference works in C and how to modify values in functions.
    Hint: Use a pointer as a function parameter and change the value inside the function.
*/

#include <stdio.h>
#include <stdlib.h>

void modify_value(int *pPointer){

   *pPointer =  30; 
}

int main(void){ 

    int x = 10; // starting value for var x 
    printf("Value of x before function: %d \n",x);
    
    modify_value(&x); 
    printf("Value of x after function: %d \n",x );




    return 0; 
}


