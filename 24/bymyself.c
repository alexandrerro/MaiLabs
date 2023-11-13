#include "mytree.h"
#include <ctype.h>

stack new_stack() {
    stack a;
    a.head = NULL;
    return a;
}

Node* create_node(Type type, int val, int rang) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = type;
    n->val = val;
    n->rang = rang;
    n->l = n->r = NULL;
    return n;
}

tree new_tree() {
    tree a;
    a.root = NULL;
    return a;
}

void push(stack* n, Node* a) {
    a->l = n->head;
    n->head = a;
}

Node* delet(stack* n) {
    Node* t = n->head;
    if (n->head) {
        n->head = t->l;
        t->l = t->r = NULL;
    }
    return t;
}

void stack_push(stack* st, stack* res, Node* n) {
    if (n->type == OPERATOR && n->val != 1) {
        Node* t;
        while ((t = delet(st)) && (t->type != OPERATOR || t->val != 1)) {
            push(res, t);
            free(t);
        }
        free(n);
    } else if (n->type == SIGN) {
        Node* t;
        while ((t = delet(st)) && (n->rang <= t->rang)) {
            push(res, t);
            free(t);
        }
        if (t) push(st, t);
        push(st, n);
    } else {
        push(res, n);
    }
}

Node* add(Node* n, stack* s) {
    if (n->type != NUMBER && n->type != VARIABLE) {
        n->l = add(delet(s), s);
        n->r = add(delet(s), s);
    }
    return n;
}

void build(tree* t, stack* s) {
    t->root = delet(s);
    t->root->l = add(delet(s), s);
    t->root->r = add(delet(s), s);
}

void decoding(Node* n) {
    if (n->type == SIGN) {
        char sign_chars[] = {'-', '+', '*', '/', '^'};
        printf("%c", sign_chars[n->val]);
    } else if (n->type == VARIABLE) {
        printf("%c", n->ch);
    } else if (n->type == NUMBER) {
        printf("%d", n->val);
    }
}

void print_tree(Node* root, int n) {
    if (!root) return;
    print_tree(root->r, n + 1);
    for (int i = 0; i < n; i++) printf("\t");
    decoding(root);
    printf("\n");
    print_tree(root->l, n + 1);
}

Node* copy(Node* a) {
    Node* n = create_node(a->type, a->val, a->rang);
    n->ch = a->ch;
    if (a->l) n->l = copy(a->l);
    if (a->r) n->r = copy(a->r);
    return n;
}

bool solving(Node* n) {
    if (n->type == SIGN && n->val == 4 && n->l->type == SIGN && n->l->r && n->l->r->val == 1) {
        Node *a = n->r, *b = n->l->l, *c = n->l->r;
        Node *a1 = copy(a), *a2 = copy(a), *b1 = copy(b), *c1 = copy(c);
        n->val = 2; n->rang = 2;
        n->r = create_node(SIGN, 2, 2); n->r->r = a2; n->r->l = b1;
        n->l->val = 2; n->l->rang = 2; n->l->r = a1; n->l->l = c1;
        return true;
    }
    bool p = false, q = false;
    if (n->l) p = solving(n->l);
    if (n->r) q = solving(n->r);
    return p || q;
}

void transform(tree* t) {
    while (t->root && solving(t->root));
}

void print_node(Node* n, int l, int r) {
    if (n->type == NUMBER || n->type == VARIABLE) {
        for (int i = 0; i < l; i++) printf("(");
        if (n->type == NUMBER) printf("%d", n->val);
        else printf("%c", n->ch);
        for (int i = 0; i < r; i++) printf(")");
    } else {
        if (n->r && n->r->type == SIGN && n->r->rang < n->rang)
            print_node(n->r, l + 1, 1);
        else if (n->r && (n->r->type == 1 || n->r->type == VARIABLE))
            print_node(n->r, l, 0);
        else
            print_node(n->r, l, 0);
        decoding(n);
        if (n->l && n->l->type == SIGN && n->l->rang < n->rang)
            print_node(n->l, 1, r + 1);
        else if (n->l && (n->l->type == 1 || n->l->type == VARIABLE))
            print_node(n->l, 0, r);
        else
            print_node(n->l, 0, r);
    }
}

void print_infix(tree* t) {
    print_node(t->root, 0, 0);
    printf("\n");
}

void free_node(Node* n) {
    if (n->l) free_node(n->l);
    if (n->r) free_node(n->r);
    free(n);
}

void free_tree(tree* tr) {
    free_node(tr->root);
    tr->root = NULL;
}

#include "mytree.h"
#include <ctype.h>

int main() {
    stack st = new_stack();
    stack result = new_stack();
    Node* n = create_node(OPERATOR, 1, -1);
    char symb;
    printf("Введите выражение:\n");
    scanf("%c", &symb);
    while (symb != '\n') {
        if (isdigit(symb)) {
            if (n->type == NUMBER || n->type == VARIABLE) 
                n->val = n->val * 10 + (symb - '0');
            else {
                stack_push(&st, &result, n);
                n = create_node(NUMBER, symb - '0', -1);
            }
        } else if (isalpha(symb)) {
            if (n->type == NUMBER || n->type == VARIABLE) {
                push(&result, n);
                stack_push(&st, &result, create_node(SIGN, 2, 2));
                n = create_node(VARIABLE, CL_BRACK, -1);
                n->ch = symb;
            } else {
                stack_push(&st, &result, n);
                n = create_node(VARIABLE, CL_BRACK, -1);
                n->ch = symb;
            }
        } else {
            switch (symb) {
                case '(':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(OPERATOR, OP_BRACK, -1);
                    break;
                case ')':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(OPERATOR, CL_BRACK, -1);
                    break;
                case '-':
                    if (n->type == NUMBER || n->type == VARIABLE) {
                        push(&result, n);
                        n = create_node(SIGN, MIN, 1);
                    } else if (n->type == OPERATOR && n->val != 1) {
                        stack_push(&st, &result, n);
                        n = create_node(SIGN, MIN, 1);
                    } else {
                        stack_push(&st, &result, n);
                        push(&result, create_node(NUMBER, -1, -1));
                        n = create_node(SIGN, MULT, 2);
                    }
                    break;
                case '+':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, PLUS, 1);
                    break;
                case '*':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, MULT, 2);
                    break;
                case '/':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, DIV, 3);
                    break;
                case '^':
                    if (n->type == NUMBER || n->type == VARIABLE)
                        push(&result, n);
                    else
                        stack_push(&st, &result, n);
                    n = create_node(SIGN, DEG, 4);
                    break;
            }
        }
        scanf("%c", &symb);
    }
    if (n->type == NUMBER || n->type == VARIABLE)
        push(&result, n);
    else
        stack_push(&st, &result, n);
    stack_push(&st, &result, create_node(OPERATOR, CL_BRACK, -1));

    tree tree_ = new_tree();
    build(&tree_, &result);

    printf("Дерево исходного выражения:\n");
    printf("\n--------------------------------------------------------------------------\n");
    print_tree(tree_.root, 1);
    printf("\n--------------------------------------------------------------------------\n");

    transform(&tree_);
    printf("Преобразованное выражение:\n");
    print_infix(&tree_);
    printf("\n");
    printf("Дерево преобразованного выражения:\n");
    printf("\n--------------------------------------------------------------------------\n");
    print_tree(tree_.root, 1);
    printf("\n--------------------------------------------------------------------------\n");
    free_tree(&tree_);
    return 0;
}
