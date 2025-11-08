#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>

struct node {
    char inf[256];  
    int priority;   
    struct node* next;
};

struct node* head = NULL, * last = NULL;           
struct node* queue_head = NULL, * queue_last = NULL; 
struct node* stack_head = NULL;                    

int dlinna = 0;
int queue_length = 0;  
int stack_length = 0;  

void queue_enqueue(void);
void queue_dequeue(void);
void stack_push(void);
void stack_pop(void);
void review_queue(void);
void review_stack(void);

void spstore_priority(void);
void spstore(void);
void review(void);
void del(char* name);
struct node* find(char* name);
struct node* get_struct(void);

struct node* get_struct_priority(void) {
    struct node* p = NULL;
    char s[256];
    int pr;  

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%s", s);

    printf("Введите приоритет объекта: ");
    scanf("%d", &pr);

    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->inf, s);
    p->priority = pr;  
    p->next = NULL;

    return p;
}

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%s", s);

    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->inf, s);
    p->priority = 0; 
    p->next = NULL;

    return p;
}

struct node* get_struct_simple(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%s", s);

    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->inf, s);
    p->priority = 0;
    p->next = NULL;

    return p;
}

void queue_enqueue(void) {
    struct node* p = get_struct_simple();
    if (p == NULL) return;

    if (queue_head == NULL) {
        queue_head = p;
        queue_last = p;
    } else {
        queue_last->next = p;
        queue_last = p;
    }
    
    queue_length++;
}

void queue_dequeue(void) {
    if (queue_head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = queue_head;
    printf("Удален из очереди: %s\n", temp->inf);
    
    queue_head = queue_head->next;
    free(temp);
    
    if (queue_head == NULL) {
        queue_last = NULL;
    }
    
    queue_length--;
}

void stack_push(void) {
    struct node* p = get_struct_simple();
    if (p == NULL) return;

    p->next = stack_head;
    stack_head = p;
    
    stack_length++;
}

void stack_pop(int position) {
    if (stack_head == NULL) {
        printf("Стек пуст\n");
        return;
    }

    if (position < 1 || position > stack_length) {
        printf("Неверная позиция! Допустимый диапазон: 1-%d\n", stack_length);
        return;
    }

    struct node* temp = stack_head;

    if (position == 1) {
        stack_head = stack_head->next;
        printf("Удален из стека (позиция %d): %s\n", position, temp->inf);
        free(temp);
        stack_length--;
        return;
    }

    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
    }

    struct node* to_delete = temp->next;
    temp->next = to_delete->next;
    printf("Удален из стека (позиция %d): %s\n", position, to_delete->inf);
    free(to_delete);
    stack_length--;
    stack_length--;
}

void review_queue(void) {
    struct node* struc = queue_head;
    int position = 1;

    if (queue_head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь:\n");
    while (struc) {
        printf("Позиция %d: Имя: %s\n", position, struc->inf);
        struc = struc->next;
        position++;
    }

    printf("Всего элементов в очереди: %d\n", position - 1);
}

void review_stack(void) {
    struct node* struc = stack_head;
    int position = 1; 

    if (stack_head == NULL) {
        printf("Стек пуст\n");
        return;
    }

    printf("Стек (всего элементов: %d):\n", stack_length);
    while (struc) {
        printf("Позиция %d: Имя: %s\n", position, struc->inf);
        struc = struc->next;
        position++;
    }
}

void spstore_priority(void) {
    struct node* p = NULL;
    struct node* current = NULL;
    struct node* prev = NULL;

    p = get_struct_priority();
    if (p == NULL) {
        return;
    }

    if (head == NULL || p->priority > head->priority) {
        p->next = head;
        head = p;
        if (head->next == NULL) {
            last = head;
        }
    }
    else {
        current = head;
        while (current != NULL && current->priority >= p->priority) {
            prev = current;
            current = current->next;
        }

        prev->next = p;
        p->next = current;

        if (current == NULL) {
            last = p;
        }
    }

    dlinna++;
    printf("Элемент с приоритетом %d добавлен\n", p->priority);
}

void spstore(void) {
    struct node* p = NULL;
    p = get_struct();
    if (head == NULL && p != NULL) {
        head = p;
        last = p;
    }
    else if (head != NULL && p != NULL) {
        last->next = p;
        last = p;
    }
    return;
}

void review(void) {
    struct node* struc = head;
    if (head == NULL) {
        printf("Основной список пуст\n");
        return;
    }

    printf("Список:\n");
    while (struc) {
        printf("Имя: %s, Приоритет: %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

struct node* find(char* name) {
    struct node* struc = head;
    int found = 0; 

    if (head == NULL) {
        printf("Список пуст\n");
        return NULL;
    }

    printf("Найденные элементы:\n");
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            printf("Элемент: %s\n", struc->inf);
            found = 1;
        }
        struc = struc->next;
    }

    if (!found) {
        printf("Элемент не найден\n");
        return NULL;
    }

    struc = head;
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            return struc; 
        }
        struc = struc->next;
    }

    return NULL;
}

void del(char* name) {
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0) {
        flag = 1;
        head = struc->next;
        free(struc);
        struc = head;
    }
    else {
        prev = struc;
        struc = struc->next;
    }

    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            flag = 1;
            if (struc->next) {
                prev->next = struc->next;
                free(struc);
                struc = prev->next;
            }
            else {
                prev->next = NULL;
                free(struc);
                return;
            }
        }
        else {
            prev = struc;
            struc = struc->next;
        }
    }

    if (flag == 0) {
        printf("Элемент не найден\n");
        return;
    }
}

void find_queue(char* name) {
    struct node* struc = queue_head;
    int position = 1;
    int found = 0;

    if (queue_head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Результаты поиска в очереди:\n");
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            printf("Позиция %d: Имя: %s\n", position, struc->inf);
            found = 1;
        }
        struc = struc->next;
        position++;
    }

    if (!found) {
        printf("Элемент не найден в очереди\n");
    }
}

void find_stack(char* name) {
    struct node* struc = stack_head;
    int position = 1;
    int found = 0;

    if (stack_head == NULL) {
        printf("Стек пуст\n");
        return;
    }

    printf("Результаты поиска в стеке:\n");
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            printf("Позиция %d: Имя: %s\n", position, struc->inf);
            found = 1;
        }
        struc = struc->next;
        position++;
    }

    if (!found) {
        printf("Элемент не найден в стеке\n");
    }
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    int choice;
    char name[256];
    int posStack;

    do {
        printf("\n");
        printf("1. Добавить элемент с приоритетом\n");  
        printf("2. Добавить элемент в конец\n");
        printf("3. Просмотреть список\n");
        printf("4. Найти элемент в списке\n");
        printf("5. Удалить элемент из списка\n");
        printf("6. Добавить в очередь\n");
        printf("7. Удалить из очереди\n");
        printf("8. Просмотреть очередь\n");
        printf("9. Найти в очереди\n");  
        printf("10. Добавить в стек\n");
        printf("11. Удалить из стека\n");
        printf("12. Просмотреть стек\n");
        printf("13. Найти в стеке\n");  
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            spstore_priority(); 
            break;
        case 2:
            spstore();
            break;
        case 3:
            review();
            break;
        case 4:
            printf("Введите имя для поиска: ");
            scanf("%s", name);
            find(name);
            break;
        case 5:
            printf("Введите имя для удаления: ");
            scanf("%s", name);
            del(name);
            break;
        case 6:
            queue_enqueue();
            break;
        case 7:
            queue_dequeue();
            break;
        case 8:
            review_queue();
            break;
        case 9:  
            printf("Введите имя для поиска в очереди: ");
            scanf("%s", name);
            find_queue(name);
            break;
        case 10:
            stack_push();
            break;
        case 11:
            printf("Введите позицию для удаления: ");
            scanf("%d", &posStack);
            stack_pop(posStack);
            break;
        case 12:
            review_stack();
            break;
        case 13:  
            printf("Введите имя для поиска в стеке: ");
            scanf("%s", name);
            find_stack(name);
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (choice != 0);

    _getch();
    return 0;
}