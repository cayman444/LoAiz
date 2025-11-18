#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

void countEdgesAndLoops(int** matrix, int size, int* edgeCount, int* loopCount) {
    *edgeCount = 0;
    *loopCount = 0;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (matrix[i][j] == 1) (*edgeCount)++;
        }
        if (matrix[i][i] == 1) (*loopCount)++;
    }
}

void analyzeVertices(int** matrix, int size) {
    printf("\nАнализ вершин:\n");

    for (int i = 0; i < size; i++) {
        int degree = 0;
        int hasLoop = 0;
        int edgeCount = 0; 

        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                if (i == j) {
                    hasLoop = 1;
                    degree += 2; 
                }
                else {
                    degree++;
                    edgeCount++;
                }
            }
        }

        if (edgeCount == 0 && !hasLoop) {
            printf("Вершина %d: Изолированная (степень: 0)", i);
        }
        else if (edgeCount == 0 && hasLoop) {
            printf("Вершина %d: Изолированная с петлей (степень: 2)", i);
        }
        else if (degree == 1) {
            printf("Вершина %d: Концевая (степень: 1)", i);
        }
        else if (edgeCount == size - 1 && !hasLoop) {
            printf("Вершина %d: Доминирующая (степень: %d)", i, degree);
        }
        else if (edgeCount == size - 1 && hasLoop) {
            printf("Вершина %d: Доминирующая с петлей (степень: %d)", i, degree);
        }
        else if (edgeCount == size - 2 && hasLoop) {
            printf("Вершина %d: Почти доминирующая с петлей (степень: %d)", i, degree);
        }
        else {
            printf("Вершина %d: Обычная (степень: %d)", i, degree);
        }

        if (hasLoop) {
            printf(" [Имеет петлю]");
        }
        printf("\n");
    }
}

void makeSymmetric(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (matrix[i][j] == 1) {
                matrix[j][i] = 1;
            }
            else if (matrix[j][i] == 1) {
                matrix[i][j] = 1;
            }
        }
    }
}

void generateLoops(int** matrix, int size, int loopProbability) {
    for (int i = 0; i < size; i++) {
        if (rand() % 100 < loopProbability) {
            matrix[i][i] = 1;
        }
    }
}

void printMatrix(int** matrix, int size) {
    printf("\nМатрица смежности неориентированного графа G:\n   ");
    for (int j = 0; j < size; j++) printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < size; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    printf("Введите размер матрицы: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Ошибка: неверный размер матрицы\n");
        return 1;
    }

    int loopProbability;
    printf("Введите вероятность образования петель (0-100%%): ");
    if (scanf("%d", &loopProbability) != 1 || loopProbability < 0 || loopProbability > 100) {
        printf("Ошибка: неверная вероятность петель\n");
        return 1;
    }

    int** matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти\n");
            return 1;
        }
    }

    srand(time(NULL));

    printf("\nГенерация неориентированного графа...\n");
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            matrix[i][j] = rand() % 2;
        }
    }

    generateLoops(matrix, size, loopProbability);
    makeSymmetric(matrix, size);

    printMatrix(matrix, size);

    int edgeCount, loopCount;
    countEdgesAndLoops(matrix, size, &edgeCount, &loopCount);

    printf("\n");
    printf("Размер графа: %d\n", edgeCount + loopCount);

    analyzeVertices(matrix, size);

    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    _getch();
    return 0;
}