#include "list.h"

List* createList() {
    List* newList = (List*)malloc(sizeof(List));
    newList->firstNode = NULL;
    return newList;
}

void deleteList(List* myList) {
    while (myList->firstNode != NULL) {
        deleteNode(myList, 0);
    }
    free(myList);
}

// Функция для создания нового узла списка
Node* createNode(ListItem value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Функция для вывода списка на экран
void printList(List* myList) {
    if (myList->firstNode == NULL) { // если список еще не создан
        printf("Список еще не создан. Создайте новый список\n");
        return;
    }
    printf("\n\n\n");
    Node* curr = myList->firstNode;
    while (curr != NULL) {
        printf("%lf  ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Функция для подсчета длины списка
int length(List* myList) {
    int count = 0;
    Node* curr = myList->firstNode;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

void deleteNode(List* myList, int position) {
    if (myList->firstNode == NULL) { // если список еще не создан
        printf("Список пуст. Добавьте элементы в список\n");
        return;
    }
    if (position >= length(myList) || position < 0) { // если позиция находится за пределами списка
        printf("Некорректная позиция элемента\n");
        return;
    }
    Node* curr = myList->firstNode;
    if (position == 0) { // если удаляемый элемент находится на первом месте
        if (curr->next == curr) { // если список состоит из одного элемента
            free(curr);
            myList->firstNode = NULL;
            return;
        }
        while (curr->next != myList->firstNode) { // иначе ищем последний элемент списка
            curr = curr->next;
        }
        curr->next = myList->firstNode->next;
        free(myList->firstNode);
        myList->firstNode = curr->next;
    } else {
        for (int i = 0; i < position - 1; i++) { // иначе ищем элемент перед удаляемым элементом
            curr = curr->next;
        }
        Node* temp = curr->next;
        curr->next = temp->next;
        free(temp); 
    }
}

void insertNode(List* myList, ListItem value, int position) {
    Node* newNode = createNode(value);
    if (myList->firstNode == NULL) {
    	myList->firstNode = newNode;
    	return;
    } else if (myList->firstNode->next == NULL) {
    	myList->firstNode->next = newNode;
    	newNode->next = myList->firstNode;
    	return;
    } else {
    	Node* curr = myList->firstNode;
    	for (int i = 0; i < position; i++) { // иначе ищем элемент на позиции position
        	curr = curr->next;
        }
    	newNode->next = curr->next; // перестраиваем связи
    	curr->next = newNode;
    	return;
    }
}
 

List* deleteMiddle(List* myList, int k) {
    int listLen = length(myList);
    if (listLen <= 2) {
        printf("Добавьте больше элементов в список\n");
        return myList;
    }
    if (k >= listLen - 2 && listLen % 2 == 0) {
        printf("Уменьшите количество удаляемых элементов\n");
        return myList;
    }
    int position = listLen / 2 - k / 2;
    for (int i = 0; i < k; i++) {
        deleteNode(myList, position);
    }
    printf("Теперь список выглядит так :\n");
    printList(myList);
    return myList;
}

