#include "mytree.h"
#include <ctype.h>

void processNumberOrVariable(stack *st, stack *result, Node **n, char symb) {
    if (isdigit(symb)) {
        if ((*n)->type == NUMBER || (*n)->type == VARIABLE)
            (*n)->val = (*n)->val * 10 + (symb - '0');
        else {
            stack_push(st, result, *n);
            *n = create_node(NUMBER, symb - '0', -1);
        }
    } else if (isalpha(symb)) {
        if ((*n)->type == NUMBER || (*n)->type == VARIABLE) {
            push(result, *n);
            stack_push(st, result, create_node(SIGN, DEG, 4));
            *n = create_node(VARIABLE, symb, -1);
        } else {
            stack_push(st, result, *n);
            *n = create_node(VARIABLE, symb, -1);
        }
    }
}

void processOperator(stack *st, stack *result, Node **n, char symb) {
    switch (symb) {
        case '+':
            handleOperator(st, result, n, symb, 1);
            break;
        case '^':
            handleOperator(st, result, n, symb, 3);
            break;
        case '(':
            stack_push(st, result, *n);
            *n = create_node(OPERATOR, 1, -1);
            break;
        case ')':
            while (*st->head && (*st->head)->type != OPERATOR) {
                stack_push(result, pop(st));
            }
            if (*st->head && (*st->head)->type == OPERATOR) {
                pop(st);
            }
            break;
    }
}

void handleOperator(stack *st, stack *result, Node **n, char symb, int newOperatorRank) {
    if ((*n)->type == NUMBER || (*n)->type == VARIABLE) {
        push(result, *n);
        *n = create_node(SIGN, symb, newOperatorRank);
    } else if ((*n)->type == OPERATOR && (*n)->val != 1) {
        stack_push(st, result, *n);
        *n = create_node(SIGN, symb, newOperatorRank);
    } else {
        stack_push(st, result, *n);
        push(result, create_node(NUMBER, 1, -1));
        *n = create_node(SIGN, symb, newOperatorRank);
    }
}

int main() {
    stack st = new_stack();
    stack result = new_stack();
    Node *n = create_node(OPERATOR, 1, -1);
    char symb;

    printf("Enter the expression:\n");
    while (scanf(" %c", &symb) == 1 && symb != '\n') {
        processNumberOrVariable(&st, &result, &n, symb);
        processOperator(&st, &result, &n, symb);
    }

    if (n->type == NUMBER || n->type == VARIABLE) {
        push(&result, n);
    } else {
        stack_push(&st, &result, n);
    }

    tree tree = new_tree();
    build(&tree, &result);

    printf("Original expression tree:\n");
    print_tree(tree.root, 1);

    transform(&tree);

    printf("Transformed expression:\n");
    print_infix(&tree);
    printf("\n");
    printf("Transformed expression tree:\n");
    print_tree(tree.root, 1);

    free_tree(&tree);
    return 0;
}
