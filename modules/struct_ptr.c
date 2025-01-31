#include <stdio.h>
#include <stdlib.h>

int main(){
    struct pixel{
        int x; //x coord of pixel
        int y; //y coord of pixel
        char color; //color  of pixel, 'R', 'G' or, 'B'
    };
    
    typedef struct pixel Pixel; // with typedef is possible to rename a type
    
    Pixel *pptr = (Pixel *)malloc(1*sizeof(Pixel));

    printf("Size of structure Pixel %lu \n", sizeof(*pptr));
    printf("Address of structure Pixel %p \n", pptr);

    pptr->x = 10;
    pptr->y = 5;
    pptr->color = 'R';
    
    printf("Pixel: %d, %d, %c\n",pptr->x, pptr->y, pptr->color);
    
}