#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <queue>
#include <climits> 

using namespace std;

void BFSD(int** G, int numG, int** GD, int s, int isDirected) {
    queue<int> q;
    int v;
    int* distance = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        distance[i] = INT_MAX;
    }

    q.push(s);
    distance[s] = 0;

    while (!q.empty()) {
        v = q.front();
        q.pop();

        for (int i = 0; i < numG; i++) {
            if (G[v][i] > 0 && distance[i] > distance[v] + G[v][i]) {
                q.push(i);
                distance[i] = distance[v] + G[v][i];
            }

            if (!isDirected && G[i][v] > 0 && distance[i] > distance[v] + G[i][v]) {
                q.push(i);
                distance[i] = distance[v] + G[i][v];
            }
        }
    }

    for (int i = 0; i < numG; i++) {
        if (distance[i] == INT_MAX) {
            GD[s][i] = -1; 
        }
        else {
            GD[s][i] = distance[i];
        }
    }

    free(distance);
}

void printM(int** Matr, int numG, const char* name) {
    printf("\n%s (%d x %d):\n", name, numG, numG);
    printf("    ");
    for (int j = 0; j < numG; j++) {
        printf("%3d ", j);
    }
    printf("\n");

    for (int i = 0; i < numG; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < numG; j++) {
            if (Matr[i][j] == -1) {
                printf("  - ");
            }
            else {
                printf("%3d ", Matr[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int** G;
    int** GD;
    int* ecc;
    int numG, current;
    int graphType; 

    printf("Введите количество вершин: ");
    scanf("%d", &numG);

    if (numG <= 0) {
        printf("Ошибка: количество вершин должно быть положительным!\n");
        return 1;
    }

    printf("Выберите тип графа:\n");
    printf("0 - Неориентированный граф\n");
    printf("1 - Ориентированный граф\n");
    printf("Ваш выбор: ");
    scanf("%d", &graphType);

    if (graphType != 0 && graphType != 1) {
        printf("Ошибка: неверный тип графа!\n");
        return 1;
    }

    ecc = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    GD = (int**)malloc(numG * sizeof(int*));

    if (!ecc || !G || !GD) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
        GD[i] = (int*)malloc(numG * sizeof(int));
        if (!G[i] || !GD[i]) {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }
    }

    printf("\nГенерация %s графа...\n",
        graphType == 0 ? "неориентированного" : "ориентированного");

    for (int i = 0; i < numG; i++) {
        ecc[i] = 0;
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0; 
            }
            else {
                if (graphType == 0) { 
                    if (j > i) { 
                        if (rand() % 2 == 1) {
                            int weight = (rand() % 10) + 1;
                            G[i][j] = weight;
                            G[j][i] = weight; 
                        }
                        else {
                            G[i][j] = 0;
                            G[j][i] = 0;
                        }
                    }
                }
                else { 
                    if (rand() % 2 == 1) {
                        G[i][j] = (rand() % 10) + 1;
                    }
                    else {
                        G[i][j] = 0;
                    }
                }
            }
            GD[i][j] = 0; 
        }
    }

    printM(G, numG, "Матрица смежности");

    printf("\nВычисление матрицы расстояний...\n");
    for (int i = 0; i < numG; i++) {
        BFSD(G, numG, GD, i, graphType);
    }
    printM(GD, numG, "Матрица расстояний");

    for (int i = 0; i < numG; i++) {
        ecc[i] = 0;
        for (int j = 0; j < numG; j++) {
            if (i != j && GD[i][j] > 0 && GD[i][j] != -1) {
                if (GD[i][j] > ecc[i]) {
                    ecc[i] = GD[i][j];
                }
            }
        }
    }

    printf("\nЭксцентриситеты вершин:\n");
    int hasValidEccentricities = 0;
    for (int i = 0; i < numG; i++) {
        if (ecc[i] > 0) {
            printf("Вершина %d: %d\n", i, ecc[i]);
            hasValidEccentricities = 1;
        }
        else {
            printf("Вершина %d: недостижима или изолирована\n", i);
        }
    }

    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 0; i < numG; i++) {
        if (ecc[i] > 0) { 
            if (ecc[i] < radius) {
                radius = ecc[i];
            }
            if (ecc[i] > diameter) {
                diameter = ecc[i];
            }
        }
    }

    if (radius == INT_MAX) {
        printf("\nГраф не имеет достижимых вершин или все вершины изолированы.\n");
    }
    else {
        printf("\nРадиус графа: %d\n", radius);
        printf("Диаметр графа: %d\n", diameter);

        printf("\nЦентральные вершины (эксцентриситет = радиусу = %d): ", radius);
        int centralFound = 0;
        for (int i = 0; i < numG; i++) {
            if (ecc[i] == radius) {
                printf("%d ", i);
                centralFound = 1;
            }
        }
        if (!centralFound) printf("нет");

        printf("\nПериферийные вершины (эксцентриситет = диаметру = %d): ", diameter);
        int peripheralFound = 0;
        for (int i = 0; i < numG; i++) {
            if (ecc[i] == diameter) {
                printf("%d ", i);
                peripheralFound = 1;
            }
        }
        if (!peripheralFound) printf("нет");
    }

    if (graphType == 1) {
        int isSymmetric = 1;
        for (int i = 0; i < numG && isSymmetric; i++) {
            for (int j = i + 1; j < numG; j++) {
                if (G[i][j] != G[j][i]) {
                    isSymmetric = 0;
                    break;
                }
            }
        }

        if (isSymmetric) {
            printf("Граф симметричный (по факту неориентированный)\n");
        }
        else {
            printf("Граф асимметричный (ориентированный)\n");
        }

        printf("\nПолустепени вершин:\n");
        for (int i = 0; i < numG; i++) {
            int outDegree = 0; 
            int inDegree = 0;  

            for (int j = 0; j < numG; j++) {
                if (G[i][j] > 0) outDegree++;
                if (G[j][i] > 0) inDegree++;
            }

            printf("Вершина %d: исходящая степень = %d, входящая степень = %d\n",
                i, outDegree, inDegree);
        }
    }

    for (int i = 0; i < numG; i++) {
        free(G[i]);
        free(GD[i]);
    }
    free(G);
    free(GD);
    free(ecc);

    _getch();
    return 0;
}