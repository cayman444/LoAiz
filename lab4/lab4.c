#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

int search_tree(struct Node* r, int value, int* count) {
    if (r == NULL) {
        return 0;
    }

    (*count)++;

    if (r->data == value) {
        printf("элемент %d под номером %d находится в дереве\n", value, *count);
        return 1;
    }

    if (value < r->data) {
        return search_tree(r->left, value, count);
    }
    else {
        return search_tree(r->right, value, count);
    }
}


int count_occurrences_with_depth(struct Node* r, int value, int depth) {
    if (r == NULL) {
        return 0;
    }

    int count = 0;
    if (r->data == value) {
        count = 1;
        printf("Найдено значение %d на глубине %d\n", value, depth);
    }

    return count +
        count_occurrences_with_depth(r->left, value, depth + 1) +
        count_occurrences_with_depth(r->right, value, depth + 1);
}

struct Node* CreateTree(struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        return r;
    }

    if (data < r->data) {
        r->left = CreateTree(r->left, data);
    }
    else {
        r->right = CreateTree(r->right, data);
    }

    return r;
}

void print_tree(struct Node* r, int l, int is_right) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1, 1);

    for (int i = 0; i < l - 1; i++) {
        printf("   ");
    }

    if (l > 0) {
        if (is_right) {
            printf(" /--");
        }
        else {
            printf(" \\--");
        }
    }

    printf("%d [глубина: %d]\n", r->data, l);
    print_tree(r->left, l + 1, 0);
}

void free_tree(struct Node* r) {
    if (r == NULL) {
        return;
    }
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;
    int search_value;

    root = NULL;
    printf("-1 - окончание построения дерева\n");

    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D);
        }
    }

    printf("Дерево:\n");
    printf("Правая сторона: /--\n");
    printf("Левая сторона:  \\--\n");
    printf("Вертикальная структура:\n");
    print_tree(root, 0, 0);
    printf("\n");

    printf("Введите значение для поиска: ");
    scanf("%d", &search_value);

    int pos = 0;
    int found = search_tree(root, search_value, &pos);

    if (!found) {
        printf("Значение %d не найдено в дереве.\n", search_value);
    }

    printf("Введите значение для подсчета: ");
    scanf("%d", &search_value);

    printf("Поиск всех вхождений значения %d:\n", search_value);
    int occurrences = count_occurrences_with_depth(root, search_value, 0);
    printf("Значение %d встречается в дереве %d раз\n", search_value, occurrences);

    free_tree(root);

    printf("Нажмите любую клавишу для выхода...");
    _getch();
    return 0;
}