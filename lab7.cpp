#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>

void DFS(int** G, int numG, int* visited, int s) {
    visited[s] = 1;
    printf("%3d", s);
    for (int i = 0; i < numG; i++) {
        if (G[s][i] == 1 && visited[i] == 0)
            DFS(G, numG, visited, i);
    }
}

int isIsolated(int** G, int numG, int vertex) {
    for (int i = 0; i < numG; i++) {
        if (i != vertex && G[vertex][i] == 1) {
            return 0; 
        }
    }
    return 1; 
}

int main() {
    setlocale(LC_ALL, "Russian");
    int** G;
    int* visited;
    int numG;
    int current;

    srand(time(NULL));

    printf("Сколько вершин?\n");
    scanf_s("%d", &numG);

    G = (int**)malloc(numG * sizeof(int*));
    visited = (int*)malloc(numG * sizeof(int));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
        for (int j = i; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                G[i][j] = G[j][i] = rand() % 2;
            }
        }
    }

    printf("\nМатрица смежности:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }

    printf("\nВведите номер стартовой вершины (0-%d): ", numG - 1);
    scanf_s("%d", &current);

    if (current < 0 || current >= numG) {
        printf("Ошибка: неверный номер вершины!\n");
    }
    else {
        if (isIsolated(G, numG, current)) {
            printf("\nВершина %d - изолированная\n", current);
        }
        else {
            printf("\nПуть обхода в глубину из вершины %d:", current);
            DFS(G, numG, visited, current);

            printf("\n\nПосещенные вершины: ");
            int visitedCount = 0;
            for (int i = 0; i < numG; i++) {
                if (visited[i]) {
                    printf("%d ", i);
                    visitedCount++;
                }
            }
            printf("\nВсего посещено вершин: %d из %d\n", visitedCount, numG);
        }
    }

    for (int i = 0; i < numG; i++) {
        free(G[i]);
    }

    free(G);
    free(visited);

    _getch();
    return 0;
}