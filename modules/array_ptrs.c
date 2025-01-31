#include <stdio.h>

int main()
{
    int arr[6] = {10, 20, 30, 40, 50, 60};
    
    printf("Array elements printed using array notation:\n");     
    for (int i=0; i<6; i++)
         printf("arr[%d] = %d\n", i, arr[i]);
    
    printf("\nArray elements printed using pointer notation:\n\n");  
    for (int i=0; i<6; i++)     
         printf("*(arr+%d) = %d\n", i, *(arr+i));

}