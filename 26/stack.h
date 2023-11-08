#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

Stack* createStack();

Node* createNode(int value);

void push(Stack* stack, int value);

bool pop(Stack* stack);

bool isEmptyStack(Stack* stack);

int stackSize(Node* top);

void freeStack(Stack* stack);

void printStack(Node* top);

void sortStack(Stack* stack);

#endif
