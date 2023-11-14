#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef double ListItem;

typedef struct Node {
    ListItem data;           
    struct Node* next;  
} Node;

typedef struct List {
	Node* firstNode;
} List;

List* createList();
Node* createNode(ListItem value);
void deleteList(List* myList);
void printList(List* myList);
int length(List* myList);
void insertNode(List* myList, ListItem value, int position);
void deleteNode(List* myList, int position);
List* deleteMiddle(List* myList, int k);

#endif 
