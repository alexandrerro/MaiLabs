#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef int TreeItem;

typedef struct Tree {
    TreeItem data;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* createNode(TreeItem data);
Tree* insert(Tree *root, TreeItem data);
Tree* findMin(Tree *root);
void printTree(Tree *root, int level);
Tree* deleteNode(Tree *root, TreeItem data);
int countNodesWithTwoSubtrees(Tree *root);
void deleteTree(Tree *root);

#endif 
