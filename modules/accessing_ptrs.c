#include <stdio.h>

int main(){

    int i1 = 10, i2 = 20, i3 = 30;

    // declaration of pointer to NULL 
    int *pPtrI = NULL;

    // pPtrI points to i2 
    pPtrI = &i2; 

    // print value of pPtrI : in this case value of i2 = 20
    printf("Value of pPtrI : %d \n", *pPtrI);
    printf("Address of pPtrI : %p \n", pPtrI);

    i3 = *pPtrI; // The value of i3 now becomes 20 -- the value of i2
    printf("New value of i3: %d \n", i3);
    *pPtrI = i1; // values of pPtrI and i2 become 10  -- the value of i1
    printf("New value of pPtrI : %d \n", *pPtrI);
    printf("Address of pPtrI : %p \n", pPtrI);

    printf("New value of i2 : %d \n", i2);

    return 0; 
}