#include <stdio.h>

/*Function prototypes*/
void printArray(int array[], int size);
void insertionSortWhile(int array[], int size); 
void insertionSortFor(int array[], int size); 


int main(){

    int data[] = {9,5,1,4,3}; 
    int data1[] = {9,5,1,4,3}; 
    int size = sizeof(data) / sizeof(data[0]); 
    insertionSortWhile(data,size); 

    printf("Sorted array with while: \n");
    printArray(data,size); 

    insertionSortFor(data1,size); 
    printf("\nSorted array with for: \n"); 
    printArray(data,size); 

    return 0; 
}

void printArray(int array[], int size){

    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]); 
    }
    printf("\n"); 
}

void insertionSortWhile(int array[], int size){

    for (int step = 1; step < size; step++)
    {
        int key = array[step];
        int j = step -1; 

        /* Compare key with each element on the left of it until an element 
           smaller than it is found */
        
       while (j>=0 && key<array[j])
       {
        array[j+1] = array[j]; 
        --j; 

       }
       array[j+1] = key;
    }
} 

void insertionSortFor(int array[], int size){
    int j,p; 
    int temp; 

    for ( p = 1; p < size; p++)
    {
        /* temp is our key value*/
        temp = array[p]; 
        for (j  = p; j> 0 && array[j-1]> temp; j--)
        {
            array[j] = array[j-1]; 
        }
        array[j] = temp; 
    }
}