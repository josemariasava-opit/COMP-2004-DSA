#include <stdio.h>
#include <stdlib.h>

// Structure for each node in the deque
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Structure for the deque itself
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty deque
struct Deque* createDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    if (deque == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    deque->front = deque->rear = NULL;
    return deque;
}

// Push: Insert at front
void push(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    
    if (deque->front == NULL) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
    printf("Pushed %d to front\n", data);
}

// Pop: Remove from front
int pop(struct Deque* deque) {
    if (deque->front == NULL) {
        printf("Deque is empty!\n");
        return -1;
    }
    
    struct Node* temp = deque->front;
    int data = temp->data;
    
    deque->front = deque->front->next;
    
    if (deque->front == NULL) {
        deque->rear = NULL;
    } else {
        deque->front->prev = NULL;
    }
    
    free(temp);
    return data;
}

// Inject: Insert at rear
void inject(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    
    if (deque->rear == NULL) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
    printf("Injected %d to rear\n", data);
}

// Eject: Remove from rear
int eject(struct Deque* deque) {
    if (deque->rear == NULL) {
        printf("Deque is empty!\n");
        return -1;
    }
    
    struct Node* temp = deque->rear;
    int data = temp->data;
    
    deque->rear = deque->rear->prev;
    
    if (deque->rear == NULL) {
        deque->front = NULL;
    } else {
        deque->rear->next = NULL;
    }
    
    free(temp);
    return data;
}

// Print the deque from front to rear
void printDeque(struct Deque* deque) {
    if (deque->front == NULL) {
        printf("Deque is empty!\n");
        return;
    }
    
    struct Node* current = deque->front;
    printf("Deque (front to rear): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Make the deque empty
void makeEmpty(struct Deque* deque) {
    while (deque->front != NULL) {
        struct Node* temp = deque->front;
        deque->front = deque->front->next;
        free(temp);
    }
    deque->rear = NULL;
    printf("Deque cleared\n");
}

int main() {
    struct Deque* deque = createDeque();
    int choice, data;
    
    while (1) {
        printf("\nEnter a choice:\n");
        printf("[1] push\n");
        printf("[2] pop\n");
        printf("[3] inject\n");
        printf("[4] eject\n");
        printf("[5] print\n");
        printf("[6] makeEmpty\n");
        printf("[7] exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &data);
                push(deque, data);
                break;
                
            case 2:
                data = pop(deque);
                if (data != -1)
                    printf("Popped value: %d\n", data);
                break;
                
            case 3:
                printf("Enter value to inject: ");
                scanf("%d", &data);
                inject(deque, data);
                break;
                
            case 4:
                data = eject(deque);
                if (data != -1)
                    printf("Ejected value: %d\n", data);
                break;
                
            case 5:
                printDeque(deque);
                break;
                
            case 6:
                makeEmpty(deque);
                break;
                
            case 7:
                makeEmpty(deque);
                free(deque);
                printf("Exiting program\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}