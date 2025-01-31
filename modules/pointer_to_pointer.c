#include <stdio.h>

int main()
{
     int i=10, *iPtr;
     int **iPtr2;
     
     iPtr = &i; // iPtr points to i 
     iPtr2 = &iPtr; // iPtr2 points to iPtr 

     printf("iPtr's address = %p\n", iPtr); // address of iPtr
     printf("iPtr's value = %d\n", *iPtr); // value of iPtr -> is the value of i 

     printf("------------------------------------- \n"); 

     printf("iPtr2's address = %p\n", iPtr2); // address of iPtr2
     printf("iPtr2's value = %p\n", *iPtr2); // value of iPtr2 -> is the address of the pointer iPtr
     printf("iPtr's value (accessed via iPtr2)= %d\n", **iPtr2);
}