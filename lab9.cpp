#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <queue>


using namespace std;

void BFSD(int** G, int numG, int* distance, int s) {
    queue<int> q;
    int v;

    distance[s] = 0;

    q.push(s);

    while (!q.empty()) {
        v = q.front();
        q.pop();
        printf("%3d", v);

        for (int i = 0; i < numG; i++) {
            if (G[v][i] == 1 && distance[i] == -1) {
                q.push(i);
                distance[i] = distance[v] + 1;
            }
        }
    }

    printf("\n\ndistance from %d to", s);
    for (int i = 0; i < numG; i++) {
        printf("\n%3d : %3d", i, distance[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int** G;
    int* distance;
    int numG, current;

    printf("input number of verts: ");
    scanf("%d", &numG);

    distance = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));

    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    for (int i = 0; i < numG; i++) {
        distance[i] = -1;

        for (int j = i; j < numG; j++) {
            G[i][j] = G[j][i] = (i == j ? 0 : rand() % 2);
        }
    }

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }

        printf("\n");
    }

    printf("Input start vert: ");
    scanf("%d", &current);

    printf("\nPath: ");

    BFSD(G, numG, distance, current);
    printf("\n\n");

    for (int i = 0; i < numG; i++) {
        free(G[i]);
    }

    free(G);
    free(distance);

    _getch();
    return 0;
}