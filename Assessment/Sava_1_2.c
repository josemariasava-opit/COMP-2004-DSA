/*
* Write a program to implement the radix or bucket sort algorithm. Your program should take the following input:
* ● the number of integers to sort, N,
* ● the maximum number of digits in any input element, M,
* ● the number of buckets to use, B
* ● a list of the N integers
* The program should store the input integers in an array of size N. It should then create the
* bucket data structure (array of lists); the number of buckets given by B. 
* Following this, your program should implement the bucket sort algorithm, as discussed in the class lecture. 
* After each pass of the algorithm, your algorithm should print the content of each bucket, from 0
* through B-1. At the end of M passes, your algorithm should print the contents of the sortedarray.
*/
#include <stdio.h>
#include <stdlib.h>

/*Struct to represent the single node of the linked list*/
typedef struct Node {
    int data;
    struct Node* next;
}Node;


/*Function prototypes*/
int countDigits(int num); 
int isValidNumber(int num, int m);
int findMaxAndDigits(int* pArray, int N, int *maxDigits);
void addToBucket(Node** head, int data);
int getDigit(int number, int position);
void printBuckets(Node* buckets[], int B);
void radixBucketSort(int* pArray, int n, int m, int b);


int main() {

    /*Local vars*/
    int n, m, b;
    
    /*Ask user to inputs value for N,M,B*/
    printf("Enter number of integers to sort, N: ");
    scanf("%d", &n);

    printf("Enter maximum number of digits allowed (M): ");
    scanf("%d", &m);

    printf("Enter number of buckets: ");
    scanf("%d", &b);
    
    /*Allocate memory for the array of integer values*/
    int* pArray = malloc(n * sizeof(int));
    /*Safety First ! Check correct allocation of memory*/
    if (pArray == NULL)
    {
        printf("Memory allocation failed! \n");
        exit(1);
    }
    
    printf("Enter the integers to be sorted (must have <= %d digits): ", m);
    
    /*
    * Ask user to inout values for array and validate them.
    * intger values cannot be more than digit>m value
    */
    for (int i = 0; i < n; i++) {
        int num;
        do {
            scanf("%d", &num);
            if (!isValidNumber(num, m)) {
                printf("Number %d has more than %d digits. Please enter a valid number: ", num, m);
            }
        } while (!isValidNumber(num, m));
        pArray[i] = num;
    }
    
    /* Call function radixBucketSort()*/
    radixBucketSort(pArray, n, m, b);
    
    /* Notify user with sorted Array*/
    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pArray[i]);
    }
    printf("\n");
    
    /* Free memory allocated for array*/
    free(pArray);
    return 0;
}

/*
* Function name     :   countDigits
* Arguments         :   num        = Integer number
* Return value/s    :   Number of digits of the number 
* Remarks           :   Counts the digit of the given number,remove last digit from n in each iteration 
*/
int countDigits(int num) {
    if (num == 0) return 1;
    int count = 0;
    while (num > 0) {
        count++;

        num /= 10;
    }
    return count;
}

/*
* Function name     :   isValidNumber
* Arguments         :   num        = Integer number
*                       m          = Integer values, M is the max number of digits from user
* Return value/s    :   1 if number is valid in the range of M digit 
*                       0 if number is not valid, out of the range of M digit
* Remarks           :   Check if a number is valid  
*/
int isValidNumber(int num, int m) {
    return countDigits(num) <= m;
}

/*
* Function name     :   findMaxAndDigits
* Arguments         :   pArray     = pointer to an array of integer values
*                       n          = Integer values, n is the number of elements of the array from user
*                       maxDigitis = Number of digits of the max value
* Return value/s    :   maxVal 
* Remarks           :   Check the maximum number inside the given array and counts the digit of this number
*/
int findMaxAndDigits(int* pArray, int n, int *maxDigits) {
    int maxVal = pArray[0];
    for (int i = 1; i < n; i++) {
        if (pArray[i] > maxVal) {
            maxVal = pArray[i];
        }
    }
    *maxDigits = countDigits(maxVal);
    return maxVal;
}

/*
* Function name     :   addToBucket
* Arguments         :   head       = double pointer to the head of the list
*                       data       = Integer value, data to be added to the node 
* Return value/s    :   --- 
* Remarks           :   Adds a new node at the end of a singly linked list. Creates a new list if empty.
*                       Handles memory allocation failures with error checking.
*/
void addToBucket(Node** head, int data) {
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
    /*Initialize the new node with data and NULL next pointer*/
    newNode->data = data;
    newNode->next = NULL;
    
    /* If list is empty, make new node the head*/
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    /* Find the last node*/
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    /*Connect the last node to the new node*/
    current->next = newNode;
}

/*
* Function name     :   getDigit
* Arguments         :   number       = Integer value to extract digit from
*                       position     = position of digit to extract (from right to left) 
* Return value/s    :   number       = Integer value (the digit at specified position) 
* Remarks           :   Extracts a specific digit from a number at given position.
*                       Position 1 gives rightmost digit, position 2 gives second from right, etc
*/
int getDigit(int number, int position) {
    while (position > 1) {
        number /= 10;
        position--;
    }
    return number % 10;
}

/*
* Function name     :   printBuckets
* Arguments         :   buckets      = array of Node pointers representing bucket heads
*                       b            = Integer value representing number of buckets 
* Return value/s    :   --- 
* Remarks           :   Prints the contents of all buckets in the radix sort algorithm.
*                       Each bucket is printed on a new line with its index and all contained values.
*/
void printBuckets(Node* buckets[], int b) {
    /* Loop  through each bucket*/
    for (int i = 0; i < b; i++) {
        printf("Bucket %d: ", i);
        /*Loop through all nodes in current bucket*/
        Node* current = buckets[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}


/*
* Function name     :   radixBucketSort
* Arguments         :   pArray      = pointer to array of integers to be sorted
*                       n           = integer value representing number of elements in array
*                       m           = integer value representing maximum value possible 
*                       b           = integer value representing number of buckets
* Return value/s    :   --- 
* Remarks           :   Sorts numbers by processing each digit position from least to most significant.
*                       Dynamically allocates and frees memory for buckets.
*                       Prints intermediate steps for visualization.
*/
void radixBucketSort(int* pArray, int n, int m, int b) {

    int actualDigits;
    int maxVal = findMaxAndDigits(pArray, n, &actualDigits);
    
    printf("\nLargest number in array: %d (has %d digits)\n", maxVal, actualDigits);
    printf("Will perform %d passes\n", actualDigits);
    
    Node** buckets = malloc(b * sizeof(struct Node*));
    
    for (int pass = 1; pass <= actualDigits; pass++) {
        /* Initialize buckets*/
        for (int i = 0; i < b; i++) {
            buckets[i] = NULL;
        }
        
        /* Distribute numbers into buckets*/
        for (int i = 0; i < n; i++) {
            int digit = getDigit(pArray[i], pass);
            addToBucket(&buckets[digit], pArray[i]);
        }
        
        printf("\nAfter Pass %d:\n", pass);
        printBuckets(buckets, b);
        
        /* Collect numbers from buckets*/
        int index = 0;  
        /* Go from 0 to b-1*/
        for (int i = 0; i < b; i++) {  
            Node* current = buckets[i];
            while (current != NULL) {
                pArray[index++] = current->data;
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
    }
    
    free(buckets);
}