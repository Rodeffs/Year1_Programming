#include <stdio.h>
#define N 14 // Порядок матрицы
int data_change(int y, int x) {
    int n = N - 1; // Конечное значение, т.к. у нас отсчёт идёт от нуля, но в матрице N элементов, крайним будет элемент n
    if (x == 0) {
        if (y == 0)
            return 1; // Значение самой первой ячейки всегда 1
        if (y % 2 != 0)
            return data_change(y-1, x) + 1;
        if (y % 2 == 0)
            return data_change(y-1, x+1) + 1;
    }
    if (y == 0) {
        if (x % 2 == 0)
            return data_change(y, x-1) + 1;
        if (x % 2 != 0)
            return data_change(y+1, x-1) + 1;
    }
    if (x == n) {
        if ( ((n % 2 == 0)&&(y % 2 != 0)) || ((n % 2 != 0)&&(y % 2 == 0)) )
            return data_change(y+1, x-1) + 1;
        if ( ((n % 2 != 0)&&(y % 2 != 0)) || ((n % 2 == 0)&&(y % 2 == 0)) || (y == n) )
            return data_change(y-1, x) + 1;
    }
    if (y == n) {
        if ( ((n % 2 != 0)&&(x % 2 == 0)) || ((n % 2 == 0)&&(x % 2 != 0)) )
            return data_change(y, x-1) + 1;
        if ( ((n % 2 != 0)&&(x % 2 != 0)) || ((n % 2 == 0)&&(x % 2 == 0)) )
            return data_change(y-1, x+1) + 1;
    }
    if ((x + y) % 2 == 0)
        return data_change(y-1, x+1) + 1;
    return data_change(y+1, x-1) + 1;
    }
int main(int argc, char *argv[]) {
    int table[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            table[i][j] = data_change(i, j);
            printf("%d%s", table[i][j], table[i][j] >= 100 ? " " : table[i][j] >= 10 ? "  " : "   "); // костыль, чтоб таблица красиво выводилась (некрасиво выводится при N > 30)
        }
        printf("\n");
    }
    return 0;
}
/* Более понятная запись:
#include <stdio.h>
#define N 7 // Порядок матрицы

int data_change(int y, int x) {
    // y - строка, x - столбец

    int n = N - 1; // Конечное значение, т.к. у нас отсчёт идёт от нуля, но в матрице N элементов, крайним будет элемент n

    if (x == 0) {

        if (y == 0)
            return 1; // Значение самой первой ячейки всегда 1

        if (y % 2 != 0)
            return data_change(y-1, x) + 1;

        if (y % 2 == 0)
            return data_change(y-1, x+1) + 1;
    }

    if (y == 0) {

        if (x % 2 == 0)
            return data_change(y, x-1) + 1;

        if (x % 2 != 0)
            return data_change(y+1, x-1) + 1;

    }

    if (x == n) {

        if ((n % 2 == 0)&&(y % 2 != 0))
            return data_change(y+1, x-1) + 1;

        if ((n % 2 != 0)&&(y % 2 != 0))
            return data_change(y-1, x) + 1;

        if ((n % 2 == 0)&&(y % 2 == 0))
            return data_change(y-1, x) + 1;

        if ((n % 2 != 0)&&(y % 2 == 0))
            return data_change(y+1, x-1) + 1;

        if (y == n)
            return data_change(y-1, x) + 1;
    }

    if (y == n) {

        if ((n % 2 != 0)&&(x % 2 == 0))
            return data_change(y, x-1) + 1;

        if ((n % 2 != 0)&&(x % 2 != 0))
            return data_change(y-1, x+1) + 1;

        if ((n % 2 == 0)&&(x % 2 != 0))
            return data_change(y, x-1) + 1;

        if ((n % 2 == 0)&&(x % 2 == 0))
            return data_change(y-1, x+1) + 1;
    }

    if ((x + y) % 2 == 0)
        return data_change(y-1, x+1) + 1;

    else return data_change(y+1, x-1) + 1;
}

int main(int argc, char *argv[]) {

    int table[N][N];

    // i - строка, j - столбец

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            table[i][j] = data_change(i, j); // Присвоение значение каждому элементу

            printf(" %d", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}
*/