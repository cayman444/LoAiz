#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_SIZE 10

 int main(void) {
     srand(time(NULL));
     setlocale(LC_ALL, "Rus");

     range();
     randomArr();
     inputmass();
     sumArr2();
     sumArr();
     studentSearch();

    _getch();
}

   range() {
     printf("Задание 1\n");

     int temp, n = 10, i = 0;

     int a[10] = { 0,1,2,3,4,5,6,7,8,9 };

     int min = a[0];
     int max = a[0];

     while (i < n / 2) {

         temp = a[i];
         a[i] = a[9 - i];
         a[9 - i] = temp;

         if (a[i] < min) {
             min = a[i];
         }

         if (a[i] > max) {
             max = a[i];
         }

         i++;
     }

     i = 0;

     while (i < n) printf(" %d\n", a[i++]);

     int res = max - min;

     printf("min: %d\n", min);
     printf("max: %d\n", max);
     printf("max - min: %d\n", res);

     printf("\n");
}

   randomArr() {
     printf("Задание 2\n");

     int arrNumbers[10];

     for (int i = 0; i < 10; i++) {
         int randomNumber = rand();
         arrNumbers[i] = randomNumber;
     }

     int lengthArr = sizeof(arrNumbers) / sizeof(arrNumbers[0]);

     for (int i = 0; i < lengthArr; i++) {
         printf("arr[%d]: %d\n", i, arrNumbers[i]);
     }

     printf("\n");
 }

   inputmass() {
       printf("Задание 3\n");

       int length;
       printf("Введите длину массива: ");
       scanf("%d", &length);

       printf("длина массива: %d\n", length);

       int* arr = (int*)malloc(length * sizeof(int));

       for (int i = 0; i < length; i++) {
           printf("Введите элемент arr[%d]: ", i);
           scanf("%d", &arr[i]);
       }

       printf("Содержимое массива:\n");
       for (int i = 0; i < length; i++) {
           printf("arr[%d]: %d\n", i, arr[i]);
       }

       printf("\n");
   }

   sumArr() {
       printf("Задание 4\n");

       int arr[3][3] = {
           {1, 2, 3},
           {5, 6, 7},
           {9, 10, 11}
       };

       const int rows = 3;
       const int cols = 3;
       int size;

       printf("Введите размер квадратного массива:");
       scanf("%d", &size);

       int** arr2 = (int**)malloc(size * sizeof(int*));
       for (int i = 0; i < size; i++) {
           arr2[i] = (int*)malloc(size * sizeof(int));
       }

       printf("Заполняем массив случайными числами от -40 до 10:\n");
       for (int i = 0; i < size; i++) {
           for (int j = 0; j < size; j++) {
               arr2[i][j] = rand() % 51 - 40; }
          
       }

       printf("Исходный массив:\n");
       for (int i = 0; i < size; i++) {
           for (int j = 0; j < size; j++) {
               printf("%4d ", arr2[i][j]);
           }
           printf("\n");
       }
       printf("\n");


       int negative_sum = 0;

       for (int i = 0; i < size; i++) {
           for (int j = 0; j < size; j++) {
               if (arr2[i][j] < 0) {
                   negative_sum += arr2[i][j];
               }
           }
       }

       printf("Сумма всех отрицательных чисел: %d\n", negative_sum);

       printf("Исходный массив:\n");
       for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
               printf("%3d ", arr[i][j]);
           }
           printf("\n");
       }
       printf("\n");

       printf("Сумма по строкам:\n");
       for (int i = 0; i < 3; i++) {
           int row_sum = 0;
           for (int j = 0; j < 3; j++) {
               row_sum += arr[i][j];
           }
           printf("Строка %d: %d\n", i, row_sum);
       }
       printf("\n");

       printf("Сумма по столбцам:\n");
       for (int j = 0; j < 3; j++) {
           int col_sum = 0;
           for (int i = 0; i < 3; i++) {
               col_sum += arr[i][j];
           }
           printf("Столбец %d: %d\n", j, col_sum);
       }
   }

   studentSearch() {
       setvbuf(stdin, NULL, _IONBF, 0);
       setvbuf(stdout, NULL, _IONBF, 0);

       int i;
       struct student
       {
           char famil[20];
           char name[20], facult[20];
           char Nomzach[20];
       } stud[3];

       for (int i = 0; i < 3; i++) {
           printf("Введите фамилию студента %d: ", i + 1);
           scanf("%s", stud[i].famil);

           printf("Введите имя студента: ", stud[i].famil);
           scanf("%s", stud[i].name);

           printf("Введите факультет студента: ");
           scanf("%s", stud[i].facult);

           printf("Введите номер зачётки студента: ");
           scanf("%s", stud[i].Nomzach);
           printf("\n");
       }

       
       char search_famil[20];
       char search_nomzach[20];
       char search_facult[20];
       char search_fied[20];

       int found = 0;

       printf("\nВведите поле для поиска: ");
       scanf("%s", search_fied);
       for (int i = 0; i < 3; i++) {
           if (strcmp(stud[i].famil, search_fied) == 0 || strcmp(stud[i].name, search_fied) == 0 || strcmp(stud[i].facult, search_fied) == 0 || strcmp(stud[i].Nomzach, search_fied) == 0) {
           printf("Найден: %s %s, факультет: %s, номер зачётки: %s\n",
               stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
           found = 1;
           }
       };

 
       if (!found) {
           printf("Студент с фамилией '%s' не найден\n", search_famil);
       }
       

       printf("\nВведите номер зачетки поиска: ");
       scanf("%d", &search_nomzach);
       for (int i = 0; i < 3; i++) {
           if (stud[i].Nomzach == search_nomzach) {
               printf("Найден: %s %s, факультет: %s, номер зачётки: %d\n",
                   stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
               found = 1;
           }
       }

       if (!found) {
           printf("Студент с номером зачетки '%d' не найден\n", search_nomzach);
       }
     

       printf("\nВведите факультет для поиска: ");
       scanf("%s", search_facult);
       for (int i = 0; i < 3; i++) {
           if (strcmp(stud[i].facult, search_facult) == 0) {
               printf("Найден: %s %s, факультет: %s, номер зачётки: %d\n",
                   stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
               found = 1;
           }
       }

       if (!found) {
           printf("Студенты на факультете '%s' не найдены\n", search_facult);
       }
   }


    sumArr2() {
       printf("Задание 4\n");

       int size;
       int percent;

       printf("Введите размер квадратного массива:");
       scanf("%d", &size);

       printf("Введите вероятность появления 1 (0-100%%): ");
       scanf("%d", &percent);

       srand(time(NULL));

       int** arr = (int**)malloc(size * sizeof(int*));
       for (int i = 0; i < size; i++) {
           arr[i] = (int*)malloc(size * sizeof(int));
       }

       for (int i = 0; i < size; i++) {
           for (int j = 0; j < size; j++) {
               int random_value = rand() % 100 + 1; 
               arr[i][j] = (random_value <= percent) ? 1 : 0;
           }
       }

       printf("Исходный массив (вероятность 1: %d%%):\n", percent);
       for (int i = 0; i < size; i++) {
           for (int j = 0; j < size; j++) {
               printf("%3d ", arr[i][j]);
           }
           printf("\n");
       }
       printf("\n");

       printf("Сумма по строкам:\n");
       for (int i = 0; i < size; i++) {
           int row_sum = 0;
           for (int j = 0; j < size; j++) {
               row_sum += arr[i][j];
           }
           printf("Строка %d: %d\n", i, row_sum);
       }
       printf("\n");

       printf("Сумма по столбцам:\n");
       for (int j = 0; j < size; j++) {
           int col_sum = 0;
           for (int i = 0; i < size; i++) {
               col_sum += arr[i][j];
           }
           printf("Столбец %d: %d\n", j, col_sum);
       }
   }
   