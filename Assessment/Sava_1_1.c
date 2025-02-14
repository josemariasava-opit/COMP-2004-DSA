/*
* Hot Potato Problem (Circular Linked List)
* N people, numbered 1 to N are sitting in a circle. Starting at person 1, a hot potato is passed.
* After M passes, the person holding the hot potato is eliminated, the circle closes ranks and the
* game continues with the person who was sitting after the eliminated person picking up the hot
* potato. The last remaining person wins. Thus, if M=0, and N=5, players are eliminated in order
* and player 5 wins. If M=1 and N=5, the order of elimination is 2, 4, 1, 5.
* You have to write a program to solve the hot potato problem. You should use a circular linked list
* as the data structure for holding the player numbers. When a player is eliminated, your program
* should make the appropriate pointer adjustments so that the circular list does not get broken.
* Your program should take M and N as input, run the hot potato game while printing the person
* that is eliminated at each round, and finally print out the winner of the game
*/

#include <stdio.h>
#include <stdlib.h>

/*Struct to represent the single node of the linked list*/
typedef struct Node{   
    int data;
    struct Node* next;     
}Node;


/*Function prototypes*/
Node* createNode(int data);
Node* createCircularList(int elements); 
void  playGame(int nPeople, int mPasses);

int main(){

    /*Local vars*/
    int n, m; 


    printf("Enter N ( number of players) : ");
    scanf("%d", &n);

    printf("Enter M ( number of passes) : ");
    scanf("%d", &m); 

    playGame(n,m);

    return 0;
}

/*
* Function name     :   createNode
* Arguments         :   data        = Integer member of struct Node
* Return value/s    :   Node structure
* Remarks           :   Creates new Node, allocate the memory and assign data args value to Node 
*/
Node* createNode(int data){

    Node* newNode = malloc(sizeof(Node));

    /*
    * Safety First ! 
    * Check the correct allocation of memory for the new Node of the list 
    */
   if (newNode == NULL)
   {
    printf("Memory allocation failed! \n");
    exit(1);
   }
   
   /*Assign to new node data argument*/
   newNode->data = data;
   newNode->next = NULL;

    return newNode;
}

/*
* Function name     :   createCircularList
* Arguments         :   element      = Integer value, number of elements(nodes) in the circular list 
* Return value/s    :   headNode  
* Remarks           :   Creates the circular list, first checks the number of elements(players) for the list
*                       if less than 1 is impossible to play the game. 
*                       Creates the headNode reference and assign the data = 1 ( first player ). 
*                       Loops n times until reach the element number 
*                       At the end of the loop connect the last node of the list(currentNode) to the headNode, in this way we have a circular list 
*/
Node* createCircularList(int elements){

    /*
    * what is the minimum number of players _
    */
   if (elements < 1 )
   {
    printf("To play this game the number of player must be at least 1 \n");
    exit(1);
   }

   /*
   * Create first player - head position of the list
   * data = 1 
   */ 
   Node* headNode = createNode(1); 
   Node* currentNode = headNode; 

   /*
   * loop n times = elements
   * i starts from 2, because headNode has data = 1 ( number of player )
   */
   for (int i = 2; i <= elements; i++)
   {
    currentNode->next = createNode(i);
    currentNode = currentNode->next;
   }

   // Connect last node to HeadNode 
   currentNode->next = headNode;
   
   return headNode;
}

/*
* Function name     :   playGame
* Arguments         :   nPeople     = Integer value, number of pplayer 
*                   :   mPasses     = Integer value, number of passes of hot potato 
* Return value/s    :   ---   
* Remarks           :   Takes as input N and M, handle border line cases like number of player = 1 / number of passes = 0 
*                       creates the circular linked list and loops through it to play the game
*                       prints result of the game.
*/
void playGame(int nPeople, int mPasses){

    /*Handle only 1 player */
    if (nPeople == 1){
        printf("Winner is player 1 \n");
        /*Exit the function*/
        return; 
    }

    /*Create circularList calling functions createCircularList()*/
    Node* head = createCircularList(nPeople);    

    /*Handle wrong creation of circularList*/
    if (head == NULL) return; 

    
    Node* currentPlayer = head;
    Node* previousPlayer = NULL;

    /* Game continues until one player is alive*/
    while (currentPlayer->next != currentPlayer)
    {
        /*loop through number of passes given by user*/
        for (int i = 0; i < mPasses; i++)
        {
            previousPlayer = currentPlayer; 
            currentPlayer = currentPlayer->next; 
        }

        /*Case where M = 0, previousPlayer is NULL*/
        if (previousPlayer == NULL)
        {
            /*Find previous node*/
            previousPlayer = currentPlayer; 
            while (previousPlayer->next != currentPlayer)
            {
                previousPlayer = previousPlayer->next; 
            }
        }

        /*Eliminate current player */
        printf("Eliminated player %d\n", currentPlayer->data);

        /*Remove eliminated player from circle */
        previousPlayer->next = currentPlayer->next;
        Node* tempNode = currentPlayer;
        currentPlayer = currentPlayer->next;
        /*Free memory allocated for temp node*/
        free(tempNode);

        /*Reset previous player for the iteration of the list*/ 
        previousPlayer = NULL; 
        
    }

    /*Notify user about the winner*/
    printf("Winner is player %d \n", currentPlayer->data);
    /*Free memory allocated for currentPlayer node*/
    free(currentPlayer);
}