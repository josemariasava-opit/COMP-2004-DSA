#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct BinaryNode *Node;

struct BinaryNode
{
    ElementType Element;
    Node Left;
    Node Right;
    int lCount;
    int rCount;
};


void MakeEmpty(Node t){

    if (t != NULL)
    {
        MakeEmpty(t->Left);
        MakeEmpty(t->Right);
        free(t);
    }
}

int isPerfectTree (int n)
{
    n = n + 1;
    while (n % 2 == 0)
        n /= 2;
    
    if ( n == 1)
        return 1;
    else
        return 0;
}

Node Insert (ElementType X, Node t){


    if (t == NULL)
    {
        Node temp_node = malloc(sizeof(struct BinaryNode));
        temp_node -> Element = X;
        temp_node -> Left = NULL;
        temp_node -> Right = NULL;
        temp_node -> lCount = temp_node -> rCount = 0;
        return temp_node;
    }
    else{
        if (t -> lCount == t -> rCount)
        {
            t -> Left = Insert ( X, t -> Left); 
            t -> lCount+=1;
        }
        else 
            if (t -> rCount < t -> lCount)
                if (isPerfectTree(t->lCount)) 
                {
                    t -> Right = Insert ( X, t -> Right); 
                    t -> rCount+=1;        
                }
                else
                {
                    t -> Left = Insert ( X, t -> Left); 
                    t -> lCount+=1;         
                }
    }
    return t;
}

void PrintTree(Node t)
{
    if (t != NULL){
        PrintTree( t->Left );
        printf("%d ", t->Element);
        PrintTree( t-> Right);
    }
 
}

Node makeTree(int n, int *arr)
{
   
    Node r = NULL;

    for (int i = 0; i < n; i++)
        r = Insert(arr[i], r);

    return r;
}

Node removeNullNodes(Node t)
{
    if (t != NULL)
    {
        t -> Left = removeNullNodes(t -> Left);
        t -> Right = removeNullNodes(t -> Right);
        if ( t -> Element == -1)
        {
            //free (t);
            return NULL;
        }
    }
    return t;
}


// Uncomment the main method below to run this program on its own 
/*
int main(void)
{
    int arr [] = {9, 6, 11, 8, 5, 14, 2};

    Node r = NULL;

    for (int i = 0; i < (int) sizeof(arr)/sizeof(int); i++)
        r = Insert(arr[i], r);

    PrintTree(r);
    MakeEmpty(r);

}
 * 
*/