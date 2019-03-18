#include "stdio.h"
#include "stdlib.h"

typedef struct stack {
    int size;
    int *storage;
    int top;
} Stack;

Stack * create(int max_size) {
    Stack * stack = (Stack *) malloc(sizeof(Stack));
    stack->storage = (int *) malloc(sizeof(int) * max_size);

    stack->size = max_size;
    stack->top = -1;

    return stack;
} 

int is_full(Stack *stack) {
    return stack->top == stack->size - 1;
}

int is_empty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (is_full(stack)) {
        printf("Stack overflow. Value %d rejected.\n", value);
        return;
    }

    stack->top++;
    stack->storage[stack->top] = value;
    printf("Value %d pushed to the stack.\n", value);
}

int pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack underflow.\n");
        return INT_MIN;
    }

    stack->top--;
    printf("Value %d popped from the stack.\n", stack->storage[stack->top + 1]);
    return stack->storage[stack->top + 1];
}

void stack_print(Stack *stack) {
    printf("Stack elements: ");
    for (int i = 0; i <= stack->top; ++i) printf("%d, ", stack->storage[i]);
    printf("\n");
}

int main() {

    Stack *stack = create(5);

    push(stack, 5);
    push(stack, 6);
    push(stack, 7);
    push(stack, 8);
    push(stack, 9);
    push(stack, 10); //overflow

    stack_print(stack);

    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack); //underflow

    stack_print(stack);

    push(stack, 8);
    push(stack, 9);
    push(stack, 10);

    stack_print(stack);
    return 0;
}