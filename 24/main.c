#include "mytree.h"
#include <ctype.h>

// Process a digit or an alphabetical character in the input expression
void processNumberOrVariable(stack *st, stack *result, Node **n, char symb) {
    if (isdigit(symb)) {
        // If the current node represents a number or variable, update its value
        if ((*n)->type == NUMBER || (*n)->type == VARIABLE)
            (*n)->val = (*n)->val * 10 + (symb - '0');
        else {
            // Push the current node to the result stack and create a new node for the digit
            stack_push(st, result, *n);
            *n = create_node(NUMBER, symb - '0', -1);
        }
    } else if (isalpha(symb)) {
        // If the current node represents a number or variable, push it to the result stack,
        // create a new node for the 'deg' operator, and update the current node to represent the variable
        if ((*n)->type == NUMBER || (*n)->type == VARIABLE) {
            push(result, *n);
            stack_push(st, result, create_node(SIGN, DEG, 4));
            *n = create_node(VARIABLE, symb, -1);
        } else {
            // If the current node is an operator, push it to the result stack,
            // and update the current node to represent the variable
            stack_push(st, result, *n);
            *n = create_node(VARIABLE, symb, -1);
        }
    }
}

// Process an operator in the input expression
void processOperator(stack *st, stack *result, Node **n, char symb) {
    switch (symb) {
        case '+':
            // Handle the addition operator
            handleOperator(st, result, n, symb, 1);
            break;
        case '^':
            // Handle the exponentiation operator
            handleOperator(st, result, n, symb, 3);
            break;
        case '(':
            // Process opening parenthesis
            stack_push(st, result, *n);
            *n = create_node(OPERATOR, 1, -1);
            break;
        case ')':
            // Process closing parenthesis
            while (*st->head && (*st->head)->type != OPERATOR) {
                stack_push(result, pop(st));
            }
            if (*st->head && (*st->head)->type == OPERATOR) {
                pop(st);  // Discard the opening parenthesis
            }
            break;
    }
}

// Handle the operator, considering its precedence
void handleOperator(stack *st, stack *result, Node **n, char symb, int newOperatorRank) {
    if ((*n)->type == NUMBER || (*n)->type == VARIABLE) {
        // If the current node represents a number or variable, push it to the result stack,
        // and update the current node to represent the new operator
        push(result, *n);
        *n = create_node(SIGN, symb, newOperatorRank);
    } else if ((*n)->type == OPERATOR && (*n)->val != 1) {
        // If the current node represents an operator (other than opening parenthesis),
        // push it to the result stack, and update the current node to represent the new operator
        stack_push(st, result, *n);
        *n = create_node(SIGN, symb, newOperatorRank);
    } else {
        // If the current node represents the opening parenthesis or a number '1',
        // push it to the result stack, push a new node representing '1' to the result stack,
        // and update the current node to represent the new operator
        stack_push(st, result, *n);
        push(result, create_node(NUMBER, 1, -1));
        *n = create_node(SIGN, symb, newOperatorRank);
    }
}

int main() {
    // Initialize stacks and the current node
    stack st = new_stack();
    stack result = new_stack();
    Node *n = create_node(OPERATOR, 1, -1);
    char symb;

    // Input expression
    printf("Enter the expression:\n");
    scanf("%c", &symb);

    // Process each character in the expression
    while (symb != '\n') {
        processNumberOrVariable(&st, &result, &n, symb);
        processOperator(&st, &result, &n, symb);
        scanf("%c", &symb);
    }

    // Finalize the stacks
    if (n->type == NUMBER || n->type == VARIABLE)
        push(&result, n);
    else
        stack_push(&st, &result, n);

    stack_push(&st, &result, create_node(OPERATOR, CL_BRACK, -1));

    // Build the original expression tree
    tree tree_ = new_tree();
    build(&tree_, &result);

    // Print the original expression tree
    printf("Original expression tree:\n");
    printf("\n--------------------------------------------------------------------------\n");
    print_tree(tree_.root, 1);
    printf("\n--------------------------------------------------------------------------\n");

    // Transform the expression tree
    transform(&tree_);

    // Print the transformed expression and tree
    printf("Transformed expression:\n");
    print_infix(&tree_);
    printf("\n");
    printf("Transformed expression tree:\n");
    printf("\n--------------------------------------------------------------------------\n");
    print_tree(tree_.root, 1);
    printf("\n--------------------------------------------------------------------------\n");

    // Free the memory allocated for the expression tree
    free_tree(&tree_);
    return 0;
}
