#include "list.h"

void printMenu() {   // функция вывода меню
    printf("\nВведите номер действия\n");
    printf("0) Конец работы\n");
    printf("1) Добавить узел списка\n");
    printf("2) Удалить узел списка\n");
    printf("3) Вывести список\n");
    printf("4) Удалить из середины списка k элементов\n");
}

int main() {
    List* newList = createList(); 
    int operation; // операция вводимая пользователем
    int position;
    ListItem value;
    while (1) { // пока программа не должна быть завершена
        printMenu(); // выводим меню
        scanf("%d", &operation); // считываем с клавиатуры выбор пользователя
        printf("\n");
        switch(operation) {
            case 0: // конец работы
                deleteList(newList); // удаляем список         
                printf("Работа программы завершена\n");
                return 0; 
            case 1: // добавить узел дерева
                printf("\nВведите значение узла:\n");
                scanf("%lf", &value); // считываем данные узла введенные пользователем
                if (newList->firstNode != NULL || newList->firstNode->next != NULL) {
                	printf("\nВведите номер узла, после которого нужно вставить новый узел:\n");
                	scanf("%d", &position); // считываем номер
                	insertNode(newList, value, position); // добавляем новый узел в список
                } else {
                	insertNode(newList, value, 1);
                }
                printf("Узел успешно добавлен\n");
            	break;
            case 2: // удалить узел списка
                printf("\nВведите номер удаляемого узла\n");
                scanf("%d", &position); // считываем номер узла 
                deleteNode(newList, position); // удаляем узел с введенным номером
                if (newList->firstNode == NULL) {
        			printf("Список пуст\n");        
   				} else {        
                printf("Узел успешно удален\n");
                } break;            
            case 3: // вывести дерево
                printList(newList);
                break;           
            case 4: // Удалить из середины списка k элементов
            	int k;
            	printf("Введите количество элементов которое хотите удалить из середины\n");
            	scanf("%d", &k);
              	deleteMiddle(newList, k);  
                break;
            default: // если нажали несуществующую опцию
                printf("Такого действия не существует!\n");
                break;
        }
    }
    return 0;
}

