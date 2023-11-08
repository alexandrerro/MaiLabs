#include "stack.h"

Stack* createStack() {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->top = NULL;
    return newStack;
}

Node* createNode(int value) {
    Node* newElem = (Node*)malloc(sizeof(Node));
    newElem->data = value;
    newElem->next = NULL;
    return newElem;
}

void push(Stack* stack, int value) {
    if (stack == NULL) {
        return;
    }
    Node* newNode = createNode(value);
    newNode->next = stack->top;
    stack->top = newNode;
    return;
}

bool pop(Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("Стек пустой\n");
        return false;
    }
    Node* deletingElem = stack->top;

    stack->top = deletingElem->next;
    free(deletingElem);
    return true;
}

bool isEmptyStack(Stack* stack) {
    return stack->top == NULL;
}

int stackSize(Node* top) { 
    if (top == NULL) {
        return 0;
    } else {
        return (1 + stackSize(top->next));
    }
}

void freeStack(Stack* stack) {
    while (!isEmptyStack(stack)) {
        pop(stack);
    }
    free(stack);
    return;
}

void printStack(Node* top) {
    if (top == NULL) {
        return;
    }
    printStack(top->next);
    printf("%d ", top->data);
    return;
}

void sortStack(Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("Стек пустой\n");
        return;
    }
    int size = stackSize(stack->top);
    int* arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = stack->top->data;
        pop(stack);
    }
    for (int i = 1; i < size; i++) {
        int k = i;
        while (k > 0 && arr[k-1] > arr[k]) {
            int temp = arr[k-1];
            arr[k-1] = arr[k];
            arr[k] = temp;
            k--;
        }
    }
    for (int i = 0; i < size ; i++) {
        push(stack, arr[i]);
    }
    free(arr);
    return;
}









