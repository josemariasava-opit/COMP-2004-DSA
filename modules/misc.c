#include <stdio.h>

int main(){

    int arr[4] = {7, 8, 9, 10}; 

    int* x = arr;

    printf("Address of x before ++ : %p \n", &x);
    printf("Value of x before ++ : %d \n", *x);
    x++;

    printf("Address if x after ++ : %p\n", &x);
    printf("Value of x after ++ : %d \n", *x);

    // printf("%d\n", x[0]);

    return 0 ; 
}