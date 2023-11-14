#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Enum to represent the type of a node
typedef enum {
    NUMBER,
    VARIABLE,
    SIGN,
    OPERATOR
} Type;

// Struct to represent a node in the expression tree
typedef struct Node {
    Type type;   // Type of the node
    int val;     // Value of the node (for numbers and operators)
    char ch;     // Character value (for variables)
    int rang;    // Operator precedence (for operators)
    struct Node* l;  // Left child
    struct Node* r;  // Right child
} Node;

// Struct to represent a stack
typedef struct Stack {
    Node* head;  // Top of the stack
} Stack;

// Struct to represent a tree
typedef struct Tree {
    Node* root;  // Root of the tree
} Tree;

// Function declarations
Stack newStack();
Node* createNode(Type type, int val, int rang);
Tree newTree();
void push(Stack* s, Node* a);
Node* pop(Stack* s);
void stackPush(Stack* st, Stack* res, Node* n);
Node* add(Node* n, Stack* s);
void build(Tree* t, Stack* s);
void decoding(Node* n);
void printTree(Node* root, int n);
Node* copy(Node* a);
bool solving(Node* n);
void transform(Tree* t);
void printNode(Node* n, int l, int r);
void printInfix(Tree* t);
void freeNode(Node* n);
void freeTree(Tree* tr);

#endif // tree_h
