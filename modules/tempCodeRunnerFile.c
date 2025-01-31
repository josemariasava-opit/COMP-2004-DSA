#include <stdio.h>

int doubleByValue(int);
int doubleByRef(int *);

int main()
{
    int n = 5;
    printf("n (before calling doubleByValue) = %d\n", n);
    printf("doubleByValue returned %d\n", doubleByValue(n));
    printf("n (before calling doubleByRef) = %d\n", n);
    printf("doubleByRef returned %d\n", doubleByRef(&n));
    printf("n (after calling doubleByRef) = %d\n", n);

}

int doubleByValue(int i){
    i *= 2;
    return i;
}

int doubleByRef(int *iptr){
    *iptr *= 2;
    return *iptr;
    
}
    