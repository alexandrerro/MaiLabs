#include "tree.h"

// функция создания нового узла дерева
Tree* createNode(TreeItem data) {
    Tree* node = (Tree*)malloc(sizeof(Tree)); // выделяем память под новый узел
    node->data = data; // присваиваем узлу данные data
    node->left = NULL; // указатель на левое поддерево null
    node->right = NULL; // указатель на правое поддерево null
    return node; // возвращаем указатель на новый созданный узел
}

// функция вставки нового узла с данными data в дерево
Tree* insert(Tree *root, TreeItem data) {
    if (root == NULL) { // если дерево пустое, создаем новый узел с данными data
        root = createNode(data); // корень нового созданного дерева равен указателю на созданный узел
    } else if (data <= root->data) { // если данные нового узла меньше или равны значению корневого узла, вставляем узел в левое поддерево
        root->left = insert(root->left, data);
    } else { // иначе вставляем в правое поддерево
        root->right = insert(root->right, data);
    }
    return root; // возвращаем указателя на корень дерева
}

// поиск узла с минимальным значением в дереве с корнем root
Tree* findMin(Tree *root) {
    while (root->left != NULL) { // пока есть левые дочерние узлы, спускаемся вниз по дереву
        root = root->left;
    }
    return root; // возврат указателя на узел с минимальным значением
}

// рекурсивная функция для вывода дерева на экран
void printTree(Tree *root, int level) { 
    if (root == NULL) { // если дерево пустое, выходим из функции
        return;
    }
    printTree(root->right, level + 1); // рекурсия для правого поддерева (следующего уровня)
    for (int i = 0; i < level; i++) { // вывод отступов для текущего уровня дерева
        printf("    ");
    }
    printf("%d\n", root->data); // вывод значения текущего узла
    printTree(root->left, level + 1); // рекурсия для левого поддерева (следующего уровня)
}

// функция удаления нужного узла из дерева
Tree* deleteNode(Tree *root, TreeItem data) {
    if (root == NULL) { // если дерево пустое, выходим из функции
        return root;
    } else if (data < root->data) { // если data меньше значения корня, идем в левое поддерево
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) { // если data больше значения корня, идем в правое поддерево
        root->right = deleteNode(root->right, data);
    } else { // иначе (если data равны) удаляем текущий узел
        if (root->left == NULL && root->right == NULL) { // если у узла нет дочерних узлов
            free(root); // освобождаем память
            root = NULL; // обнуляем указатель на удаленный узел
        } else if (root->left == NULL) { // если у узла есть только правый дочерний узел
            Tree *temp = root; // создаем временный указатель на текущий узел
            root = root->right; // указатель на текущий узел делаем равным указателю на правый дочерний узел
            free(temp); // освобождаем память
        } else if (root->right == NULL) { // если у узла есть только левый дочерний узел
            Tree *temp = root; // создаем временный указатель на текущий узел
            root = root->left; // указатель на текущий узел делаем равным указателю на правый дочерний узел
            free(temp); // освобождаем память
        } else { // если у узла есть оба дочерних узла
            Tree *temp = findMin(root->right); // находим узел с минимальным значением в правом поддереве
            root->data = temp->data; // заменяем значение текущего узла на значение найденного узла
            root->right = deleteNode(root->right, temp->data); // идем вниз к нужному узлу и удаляем
        }
    }
    return root; // возврат указателя на корень дерева
}

// подсчет количества узлов в дереве, у которых есть оба дочерних узла
int countNodesWithTwoSubtrees(Tree *root) {
    if (root == NULL) { // если дерево пустое, возвращаем 0
        return 0;
    }
    int count = 0; // счетчик узлов с двумя дочерними узлами
    if (root->left != NULL && root->right != NULL) { // если у текущего узла есть оба дочерних узла, увеличиваем счетчик
        count = 1;
    }
    count += countNodesWithTwoSubtrees(root->left) + countNodesWithTwoSubtrees(root->right); // рекурсивно считаем нужные узлы вызывая ту же функцию от левого и правого поддерева
    return count; // возврат счетчика
}

// рекурсивная функция для удаления всего дерева
void deleteTree(Tree *root) {
    if (root == NULL) { // если дерево пустое, выходим из функции
        return;
    }
    deleteTree(root->left); // вызываем ту же функцию для левого поддерева
    deleteTree(root->right); // вызываем ту же функцию для правого поддерева
    free(root); // освобождаем память
}

