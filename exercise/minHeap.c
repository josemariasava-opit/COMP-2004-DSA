#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for a min heap
typedef struct {
    int heap[MAX_SIZE];
    int size;
} MinHeap;

// Function to initialize an empty min heap
void initialize(MinHeap *h) {
    h->size = 0;
}

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to get parent index
int parent(int i) {
    return (i - 1) / 2;
}

// Function to insert a key into the min heap
void insert(MinHeap *h, int key) {
    if (h->size >= MAX_SIZE) {
        printf("Heap overflow\n");
        return;
    }
    
    // Insert the new key at the end
    h->size++;
    int i = h->size - 1;
    h->heap[i] = key;
    
    // Fix the min heap property if it is violated
    // Move the key up to its correct position
    while (i != 0 && h->heap[parent(i)] > h->heap[i]) {
        swap(&h->heap[i], &h->heap[parent(i)]);
        i = parent(i);
    }
    
    // Print the current state of the heap
    printf("After inserting %d: [", key);
    for (int j = 0; j < h->size; j++) {
        printf("%d", h->heap[j]);
        if (j < h->size - 1) printf(", ");
    }
    printf("]\n");
}

// Function to print the heap as a tree (for visualization)
void printHeapTree(MinHeap *h) {
    printf("\nFinal Min Heap Structure:\n");
    
    // Calculate the height of the heap
    int height = 0;
    int size = h->size;
    while (size > 0) {
        height++;
        size /= 2;
    }
    
    // Print level by level
    int level = 0;
    int levelSize = 1;
    int i = 0;
    
    while (level < height) {
        printf("Level %d: ", level);
        
        for (int j = 0; j < levelSize && i < h->size; j++) {
            printf("%d ", h->heap[i]);
            i++;
        }
        printf("\n");
        
        level++;
        levelSize *= 2;
    }
}

int main() {
    MinHeap h;
    initialize(&h);
    
    // Insert the given keys one by one
    int keys[] = {10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2};
    int numKeys = sizeof(keys) / sizeof(keys[0]);
    
    printf("Inserting keys into min heap:\n");
    for (int i = 0; i < numKeys; i++) {
        insert(&h, keys[i]);
    }
    
    // Print the final heap as an array
    printf("\nFinal Min Heap Array: [");
    for (int i = 0; i < h.size; i++) {
        printf("%d", h.heap[i]);
        if (i < h.size - 1) printf(", ");
    }
    printf("]\n");
    
    // Print the heap as a tree structure
    printHeapTree(&h);
    
    return 0;
}