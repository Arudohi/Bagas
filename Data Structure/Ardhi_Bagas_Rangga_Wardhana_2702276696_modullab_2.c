#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

// Define struct for node
typedef struct Node {
    char data[MAX_LENGTH];
    struct Node *next;
} Node;

// Define struct for the stack
typedef struct {
    Node *top;
} Stack;

// Function to create new node
Node *create_node(char *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL) {
        strcpy(new_node->data, data);
        new_node->next = NULL;
    }
    return new_node;
}

// Initialize the stack
void initialize(Stack *stack) {
    stack->top = NULL;
}

// Func to check if stack is empty
bool is_empty(Stack *stack) {
    return stack->top == NULL;
}

// Func to push element to stack
void push(Stack *stack, char *item) {
    Node *new_node = create_node(item);
    if (new_node != NULL) {
        new_node->next = stack->top;
        stack->top = new_node;
    } else {
        printf("Memory allocation failed. Unable to push item onto stack.\n");
    }
}

// Func to pop an element from the stack
char *pop(Stack *stack) {
    if (!is_empty(stack)) {
        Node *temp = stack->top;
        char *data = strdup(temp->data);
        stack->top = stack->top->next;
        free(temp);
        return data;
    } else {
        printf("Stack underflow!\n");
        return NULL;
    }
}

// Func to free all nodes from the stack
void free_stack(Stack *stack) {
    while (stack->top != NULL) {
        Node *temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

int main() {
    char input[MAX_LENGTH];
    Stack medicines_stack;
    initialize(&medicines_stack);

    printf("Sunib Hospital\n");
    printf("===============\n\n\n");

    while (1) {
        // input med
        while (1) {
            printf("enter the medicine name [minimum 5 medicine] ('done' to finish): ");
            fgets(input, MAX_LENGTH, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strcmp(input, "done") == 0) {
                break;
            }
            push(&medicines_stack, input);
            printf("Medicine %s added to the prescription.\n", input);
        }

        // display Medicine Prescription
        printf("\nMedicine Prescription: \n");
        int order = 1;
        while (!is_empty(&medicines_stack)) {
            printf("Take Medicine #%d: %s\n", order++, pop(&medicines_stack));
        }

        // Ask user continue or not
        printf("\nDo you want to continue? (yes/no): ");
        fgets(input, MAX_LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcasecmp(input, "yes") != 0) {
            break;
        }
    }

    free_stack(&medicines_stack);

    return 0;
}