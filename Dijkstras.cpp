#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

int** graph = NULL;
int n = 0;
int isDirected = 0;

void freeGraph() {
    if (graph != NULL) {
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        graph = NULL;
    }
    n = 0;
}

int** allocateGraph(int size) {
    int** newGraph = (int**)malloc(size * sizeof(int*));
    if (newGraph == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        newGraph[i] = (int*)malloc(size * sizeof(int));
        if (newGraph[i] == NULL) {
            for (int j = 0; j < i; j++) free(newGraph[j]);
            free(newGraph);
            return NULL;
        }
    }
    return newGraph;
}

void initGraph(int size) {
    freeGraph();

    graph = allocateGraph(size);
    if (graph == NULL) {
        printf("Ошибка выделения памяти!\n");
        n = 0;
        return;
    }

    n = size;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = 0;
        }
    }
}

int inputInt(const char* prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Ошибка! Введите целое число: ");
        while (getchar() != '\n');
    }
    return value;
}

int inputIntRange(const char* prompt, int min, int max) {
    int value;
    do {
        value = inputInt(prompt);
        if (value < min || value > max) {
            printf("Ошибка! Введите число от %d до %d: ", min, max);
        }
    } while (value < min || value > max);
    return value;
}

void printGraph() {
    if (n == 0 || graph == NULL) {
        printf("Граф не задан!\n");
        return;
    }

    printf("\nМатрица смежности (%sграф, %d вершин):\n",
        isDirected ? "ориентированный " : "неориентированный ", n);
    printf("     ");
    for (int i = 0; i < n; i++)
        printf("%4d ", i);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%4d: ", i);
        for (int j = 0; j < n; j++) {
            printf("%4d ", graph[i][j]);
        }
        printf("\n");
    }
}

void inputManual() {
    if (n == 0) {
        printf("Сначала задайте размер графа (пункт 1)!\n");
        return;
    }

    printf("Введите матрицу смежности (%dx%d):\n", n, n);
    printf("(0 - нет ребра, >0 - вес ребра)\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
                continue;
            }

            printf("graph[%d][%d]: ", i, j);
            int weight;
            scanf("%d", &weight);

            if (weight < 0) {
                printf("Вес не может быть отрицательным! Установлено 0.\n");
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = weight;

                if (!isDirected) {
                    graph[j][i] = weight;
                }
            }
        }
    }
    printf("Граф успешно введен.\n");
}

void inputRandom() {
    if (n == 0) {
        printf("Сначала задайте размер графа (пункт 1)!\n");
        return;
    }

    int maxWeight = inputIntRange("Максимальный вес ребра (1-100): ", 1, 100);
    int density = inputIntRange("Плотность графа в % (0-100): ", 0, 100);

    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;
                continue;
            }

            if ((rand() % 100) < density) {
                int weight = rand() % maxWeight + 1;
                graph[i][j] = weight;

                if (!isDirected) {
                    graph[j][i] = weight;
                }
            }
            else {
                graph[i][j] = 0;
                if (!isDirected) {
                    graph[j][i] = 0;
                }
            }
        }
    }
    printf("Случайный %sграф сгенерирован.\n", isDirected ? "ориентированный " : "неориентированный ");
}

void inputFromFile() {
    char filename[256];
    printf("Введите имя файла для загрузки: ");
    scanf("%255s", filename);

    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Ошибка открытия файла %s!\n", filename);
        return;
    }

    int fileSize;
    if (fscanf(f, "%d", &fileSize) != 1) {
        printf("Ошибка чтения размера графа из файла!\n");
        fclose(f);
        return;
    }

    if (fscanf(f, "%d", &isDirected) != 1) {
        printf("Ошибка чтения типа графа из файла!\n");
        fclose(f);
        return;
    }

    if (fileSize <= 0) {
        printf("Некорректный размер графа в файле: %d\n", fileSize);
        fclose(f);
        return;
    }

    freeGraph();
    graph = allocateGraph(fileSize);
    if (graph == NULL) {
        printf("Ошибка выделения памяти для графа!\n");
        fclose(f);
        return;
    }

    n = fileSize;
    int error = 0;

    for (int i = 0; i < n && !error; i++) {
        for (int j = 0; j < n && !error; j++) {
            if (fscanf(f, "%d", &graph[i][j]) != 1) {
                printf("Ошибка чтения элемента [%d][%d] из файла!\n", i, j);
                error = 1;
            }
            if (graph[i][j] < 0) {
                printf("Отрицательный вес ребра [%d][%d] = %d. Исправлено на 0.\n",
                    i, j, graph[i][j]);
                graph[i][j] = 0;
            }
        }
    }

    fclose(f);

    if (!error) {
        printf("Граф успешно загружен из файла %s\n", filename);
        printf("Тип: %s, Размер: %d вершин\n",
            isDirected ? "ориентированный" : "неориентированный", n);
    }
    else {
        freeGraph();
    }
}

void exportGraph() {
    if (n == 0 || graph == NULL) {
        printf("Граф не задан!\n");
        return;
    }

    char filename[256];
    printf("Введите имя файла для экспорта: ");
    scanf("%255s", filename);

    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Ошибка создания файла %s!\n", filename);
        return;
    }

    fprintf(f, "%d\n", n);
    fprintf(f, "%d\n", isDirected);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", graph[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Граф экспортирован в файл %s\n", filename);
}

void printPath(int prev[], int destination) {
    if (prev[destination] == -1) {
        printf("%d", destination);
        return;
    }

    int* path = (int*)malloc(n * sizeof(int));
    int count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = prev[current];
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }

    free(path);
}

void dijkstra(int start) {
    if (n == 0 || graph == NULL) {
        printf("Граф не задан!\n");
        return;
    }

    if (start < 0 || start >= n) {
        printf("Неверная стартовая вершина! Допустимый диапазон: 0..%d\n", n - 1);
        return;
    }

    int* dist = (int*)malloc(n * sizeof(int));
    int* visited = (int*)malloc(n * sizeof(int));
    int* prev = (int*)malloc(n * sizeof(int));

    if (dist == NULL || visited == NULL || prev == NULL) {
        printf("Ошибка выделения памяти!\n");
        if (dist) free(dist);
        if (visited) free(visited);
        if (prev) free(prev);
        return;
    }

    int hasNegativeEdge = 0;
    for (int i = 0; i < n && !hasNegativeEdge; i++) {
        for (int j = 0; j < n && !hasNegativeEdge; j++) {
            if (graph[i][j] < 0) {
                printf("Ошибка: найден отрицательный вес ребра %d->%d = %d\n",
                    i, j, graph[i][j]);
                hasNegativeEdge = 1;
            }
        }
    }

    if (hasNegativeEdge) {
        printf("Алгоритм Дейкстры не работает с отрицательными весами!\n");
        free(dist);
        free(visited);
        free(prev);
        return;
    }

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1 || minDist == INT_MAX) {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0) {
                long long newDist = (long long)dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = (int)newDist;
                    prev[v] = u;
                }
            }
        }
    }

    printf("\nСтартовая вершина: %d\n", start);
    printf("Тип графа: %s\n", isDirected ? "ориентированный" : "неориентированный");

    printf("\nКратчайшие расстояния:\n");
    for (int i = 0; i < n; i++) {
        if (i == start) {
            printf("до %d = 0 (стартовая вершина)\n", i);
        }
        else if (dist[i] == INT_MAX) {
            printf("до %d = недостижима\n", i);
        }
        else {
            printf("до %d = %d\n", i, dist[i]);
        }
    }

    printf("\nКратчайшие пути:\n");
    for (int i = 0; i < n; i++) {
        if (i != start && dist[i] != INT_MAX) {
            printf("В %d (%d): ", i, dist[i]);
            printPath(prev, i);
            printf("\n");
        }
    }

    char filename[256];
    printf("\nВведите имя файла для сохранения результатов (или нажмите Enter для пропуска): ");
    getchar();
    fgets(filename, sizeof(filename), stdin);

    filename[strcspn(filename, "\n")] = 0;

    if (strlen(filename) > 0) {
        FILE* f = fopen(filename, "w");
        if (f) {
            fprintf(f, "Исходные данные:\n");
            fprintf(f, "Стартовая вершина: %d\n", start);
            fprintf(f, "Тип графа: %s\n", isDirected ? "ориентированный" : "неориентированный");
            fprintf(f, "Количество вершин: %d\n\n", n);

            fprintf(f, "Исходная матрица смежности:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fprintf(f, "%d ", graph[i][j]);
                }
                fprintf(f, "\n");
            }

            fprintf(f, "Кратчайшие расстояния от вершины %d:\n", start);
            for (int i = 0; i < n; i++) {
                if (i == start) {
                    fprintf(f, "до %d = 0 (стартовая вершина)\n", i);
                }
                else if (dist[i] == INT_MAX) {
                    fprintf(f, "до %d = недостижима\n", i);
                }
                else {
                    fprintf(f, "до %d = %d\n", i, dist[i]);
                }
            }

            fprintf(f, "\nКратчайшие пути от вершины %d:\n", start);
            for (int i = 0; i < n; i++) {
                if (i != start && dist[i] != INT_MAX) {
                    fprintf(f, "В %d (расстояние: %d): ", i, dist[i]);

                    int* path = (int*)malloc(n * sizeof(int));
                    int count = 0;
                    int current = i;
                    while (current != -1) {
                        path[count++] = current;
                        current = prev[current];
                    }

                    for (int j = count - 1; j >= 0; j--) {
                        fprintf(f, "%d", path[j]);
                        if (j > 0) fprintf(f, " -> ");
                    }
                    fprintf(f, "\n");

                    free(path);
                }
            }

            fclose(f);
            printf("Результаты сохранены в файл %s\n", filename);
        }
        else {
            printf("Ошибка сохранения в файл %s!\n", filename);
        }
    }

    free(dist);
    free(visited);
    free(prev);

    printf("\nНажмите любую клавишу для продолжения...");
    _getch();
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (1) {
        printf("1. Задать размер графа (текущий: %d)\n", n);
        printf("2. Задать тип графа (текущий: %s)\n",
            isDirected ? "ориентированный" : "неориентированный");
        printf("3. Ввод графа вручную\n");
        printf("4. Генерация случайного графа\n");
        printf("5. Загрузить граф из файла\n");
        printf("6. Экспорт графа в файл\n");
        printf("7. Показать матрицу смежности\n");
        printf("8. Выполнить алгоритм Дейкстры\n");
        printf("0. Выход\n");

        choice = inputIntRange("Выбор: ", 0, 8);

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1: {
            int size = inputInt("Количество вершин: ");
            if (size <= 0) {
                printf("Размер должен быть положительным!\n");
                break;
            }
            initGraph(size);
            printf("Размер графа установлен в %d вершин.\n", n);
            break;
        }

        case 2:
            isDirected = inputIntRange("Тип графа (0 - неориентированный, 1 - ориентированный): ", 0, 1);
            printf("Тип графа установлен: %s\n",
                isDirected ? "ориентированный" : "неориентированный");
            break;

        case 3:
            inputManual();
            break;

        case 4:
            inputRandom();
            break;

        case 5:
            inputFromFile();
            break;

        case 6:
            exportGraph();
            break;

        case 7:
            printGraph();
            break;

        case 8: {
            if (n == 0) {
                printf("Сначала задайте граф!\n");
                break;
            }
            printf("Доступные вершины: 0..%d\n", n - 1);
            int start = inputIntRange("Начальная вершина: ", 0, n - 1);
            dijkstra(start);
            break;
        }

        default:
            printf("Неверный выбор!\n");
        }
    }

    freeGraph();

    printf("\nПрограмма завершена. Нажмите любую клавишу...");
    _getch();
    return 0;
}