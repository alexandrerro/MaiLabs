#include "mytree.h"
#include <ctype.h>

// Create a new stack and initialize it
stack newStack() {
    stack s;
    s.head = NULL;
    return s;
}

// Create a new node with the specified type, value, and rank
Node* createNode(Type type, int val, int rang) {
    Node* n = malloc(sizeof(Node));
    n->type = type;
    n->val = val;
    n->rang = rang;
    n->l = NULL;
    n->r = NULL;
    return n;
}

// Create a new tree and initialize it
tree newTree() {
    return (tree){.root = NULL};
}

// Push a node onto the stack
void push(stack* s, Node* a) {
    a->l = s->head;
    s->head = a;
}

// Pop a node from the stack
Node* pop(stack* s) {
    Node* t = s->head;
    if (s->head) {
        s->head = t->l;
        t->l = t->r = NULL;
    }
    return t;
}

// Push nodes onto the stack based on their type and rank
void stackPush(stack* st, stack* res, Node* n) {
    if (n->type == OPERATOR && n->val != 1) {
        // If the node is an operator (other than opening parenthesis),
        // push nodes from the stack to the result stack until an opening parenthesis is encountered
        Node* t;
        while ((t = pop(st)) && (t->type != OPERATOR || t->val != 1)) {
            push(res, t);
            free(t);
        }
        free(n);
    } else if (n->type == SIGN) {
        // If the node is a sign, push nodes from the stack to the result stack
        // until a node with lower or equal rank is encountered, then push the node onto the stack
        Node* t;
        while ((t = pop(st)) && (n->rang <= t->rang)) {
            push(res, t);
            free(t);
        }
        if (t) push(st, t);
        push(st, n);
    } else {
        // If the node is a number or variable, push it onto the result stack
        push(res, n);
    }
}

// Recursively add nodes to the expression tree
Node* add(Node* n, stack* s) {
    if (n->type != NUMBER && n->type != VARIABLE) {
        n->l = add(pop(s), s);
        n->r = add(pop(s), s);
    }
    return n;
}

// Build the expression tree from the stacks
void build(tree* t, stack* s) {
    t->root = pop(s);
    t->root->l = add(pop(s), s);
    t->root->r = add(pop(s), s);
}

// Decode and print the content of a node
void decoding(Node* n) {
    if (n->type == SIGN) {
        char signChars[] = {'-', '+', '*', '/', '^'};
        printf("%c", signChars[n->val]);
    } else if (n->type == VARIABLE) {
        printf("%c", n->ch);
    } else if (n->type == NUMBER) {
        printf("%d", n->val);
    }
}

// Print the expression tree in a visually appealing format
void printTree(Node* root, int n) {
    if (!root) return;
    printTree(root->r, n + 1);
    for (int i = 0; i < n; i++) printf("\t");
    decoding(root);
    printf("\n");
    printTree(root->l, n + 1);
}

// Create a copy of a node and its subtree
Node* copy(Node* a) {
    Node* n = createNode(a->type, a->val, a->rang);
    n->ch = a->ch;
    if (a->l) n->l = copy(a->l);
    if (a->r) n->r = copy(a->r);
    return n;
}

// Check and perform transformations on the expression tree
bool solving(Node* n) {
    if (n->type == SIGN && n->val == DEG) {
        Node* a = n->l;
        Node* b = n->r;
        
        // Check if 'a' is a variable 'a', '+' is the operator, and 'b' is the operator '+'
        if (a && a->type == VARIABLE && b && b->type == SIGN && b->val == PLUS) {
            Node* b_left = b->l;  // Left operand of the '+' operator
            Node* b_right = b->r; // Right operand of the '+' operator
            
            // Check if b_left and b_right are numbers (or variables, additional checks needed in this case)
            if (b_left && (b_left->type == NUMBER || (b_left->type == VARIABLE && b_left->ch == 'a')) &&
                b_right && (b_right->type == NUMBER || (b_right->type == VARIABLE && b_right->ch == 'a'))) {
                
                // Replace the expression a^(b+c) with (a^b)*(a^c)
                n->val = MULT;
                n->rang = 2;
                n->r = create_node(SIGN, DEG, 4);
                n->r->l = create_node(VARIABLE, 'a', -1);
                n->r->r = b_right;

                b->l = create_node(SIGN, DEG, 4);
                b->l->l = create_node(VARIABLE, 'a', -1);
                b->l->r = b_left;

                return true;
            }
        }
    }

    bool p = false, q = false;
    if (n->l) p = solving(n->l);
    if (n->r) q = solving(n->r);
    return p || q;
}

// Transform the expression tree by repeatedly applying solving transformations
void transform(tree* t) {
    while (t->root && solving(t->root));
}

// Print the transformed infix expression
void printNode(Node* n, int l, int r) {
    if (n->type == NUMBER || n->type == VARIABLE) {
        for (int i = 0; i < l; i++) printf("(");
        if (n->type == NUMBER) printf("%d", n->val);
        else printf("%c", n->ch);
        for (int i = 0; i < r; i++) printf(")");
    } else {
        if (n->r && n->r->type == SIGN && n->r->rang < n->rang)
            printNode(n->r, l + 1, 1);
        else if (n->r && (n->r->type == 1 || n->r->type == VARIABLE))
            printNode(n->r, l, 0);
        else
            printNode(n->r, l, 0);
        decoding(n);
        if (n->l && n->l->type == SIGN && n->l->rang < n->rang)
            printNode(n->l, 1, r + 1);
        else if (n->l && (n->l->type == 1 || n->l->type == VARIABLE))
            printNode(n->l, 0, r);
        else
            printNode(n->l, 0, r);
    }
}

// Print the transformed infix expression of the tree
void printInfix(tree* t) {
    printNode(t->root, 0, 0);
    printf("\n");
}

// Free the memory allocated for a node and its subtree
void freeNode(Node* n) {
    if (n->l) freeNode(n->l);
    if (n->r) freeNode(n->r);
    free(n);
}

// Free the memory allocated for the expression tree
void freeTree(tree* tr) {
    freeNode(tr->root);
    tr->root = NULL;
}
