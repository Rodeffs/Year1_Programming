#include <stdio.h>
#include <stdlib.h> // Здесь находится rand()

int main(int argc, char *argv[])
{
    int a = 3;

    if(a % 2 ==0) {
        printf("even\n");
    }
    else
       printf("odd\n");

    int e;
    if (a < 3) {
        e = 3;
    }
    else e = 4;

    e = (a<3 ? 2:4); // Это выражение такое же, как и оператор, описаный выше


    /* Наибольшее из 3 чисел: */
    int d = 42, b = 2, c = 99;

    if ((d > b) && (d > c))
        printf("max=d");
    else if ((b > c) && (b > d))
        printf("max=b");
    else if ((c > b) && (c > d))
        printf("max=c");

    d > b ? (d > c ? d : c) : (b > c ? b : c); // Иное решение


    // && - логическое "и"
    // || - логическое "или"
    // ! - логическое "не"


    /* Числа Фибоначчи: */
    int num1 = 1, num2 = 1;

    for (int i = 0; i < 10; i++) {
        int next = num1 + num2;
        printf("%d\n",next);
        num1 = num2; // В данном случае нельзя писать int, т.к. он перекроет видимость, и не присвоит значение старой переменной
        num2 = next;
    }


    /* Шахматная доска (x - чёрная клетка, y - белая)*/
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
           if ((i + j) % 2 == 0)
               printf("y");
           else
               printf("x");
        }
        printf("\n");
    }


    /* Массивы */

    int cont[10]; // cont - это массив из 10 элементов
    cont[0] = 1;  // первому элементу присваиваем значение 1
    cont[9] = 10; // последнему элементу присваиваем значение 10

    int numbers[10] = {0, 1, 2, 3}; // Первым 4 элементам присваивается значения в фигурных скобках, остальным присаивается 0

    int empty[10] = {0}; // пустой массив


    int matrix[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }

    // Иное решение того, вто написано выше
    int matrix2[10][10] = {0};
    for (int i = 0; i < 10; i++)
        matrix2[i][i] = 1;


    /* Генератор случайных чисел */

    rand(); // Генератор случайных чисел

    srand(5); // Задаёт seed случайной последовательности

    srand(time(0)); // seed становится временем time() - метод, возвращающий время



    /*  Сапёр   */

#define N 10 // Присваиваем значение N (размер поля)

#define M 10

    int mines[N][N] = {0};

    for (int m = 0; m < M; m++) {
        int i = rand() % N; // Присваиваем значение остатка от деления на N (он будет от 0 до N-1)
        int j = rand() % N;
        mines[i][j] = -1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (cell == -1)
                printf("*");
            else
                printf("%d",cell);
        }
        printf("\n");
    }










    return 0;
}
