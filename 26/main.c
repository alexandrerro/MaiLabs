#include "stack.h"

void printMenu() { 
    printf("\nВведите номер действия\n");
    printf("0) Конец работы\n");
    printf("1) Добавить элемент в стек\n");
    printf("2) Удалить элемент из стека\n");
    printf("3) Вывести стек\n");
    printf("4) Подсчет глубины стека\n");
    printf("5) Проверить стек на пустоту\n");
    printf("6) Вставить элемент в отсортированный стек с сохранением порядка\n");
}

int main() {
    Stack* newStack = createStack();
    while(1) {
        printMenu();
        int choose;
        int input;
        scanf("%d", &choose);
        switch(choose) {
            case 0:
                freeStack(newStack);
                printf("\nРабота программы завершена\n");
                return 0;
            case 1:
                printf("\nВведите значение элемента, который хотите добавить в стек\n");        
                scanf("%d", &input);
                push(newStack, input);
                printf("\nЭлемент '%d' успешно добавлен в стек\n",input);
                break;
            case 2:
                if (pop(newStack)) {
                printf("\nПоследний добавленный элемент успешно удален из стека\n");
                } 
                break;
            case 3:
                printStack(newStack->top);
                printf("\n");
                break;
            case 4:
                printf("\nГлубина стека = %d\n", stackSize(newStack->top));
                break;  
            case 5:
                if (!isEmptyStack(newStack)) {
                    printf("\nСтек не пуст\n");
                } else {
                    printf("\nСтек пуст\n");
                }
                break;
            case 6:
            	printf("\nВведите элемент, который нужно вставить в стек с сохранением порядка :\n");
            	scanf("%d", &input);
            	push(newStack, input);
                printf("\nПолученный стек :\n");
                sortStack(newStack);
                printStack(newStack->top);
                break;
            default:
                printf("\nВведенного действия не существует. Введите другое\n");
                break;
        }
    }
    return 0;
}
