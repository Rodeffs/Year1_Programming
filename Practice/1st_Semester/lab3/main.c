#include <stdio.h> /*               Контрольная работа №3.               */
int hex(int num, int i) { // Перевод в 16-чную систему, num - число, i - четвёрка цифр числа (у каждого числа будет ровно 8 таких четвёрок, т.к. int занимает 32 байта 32/4=8)
    int num16 = (num >> (32 - ((i+1) * 4)));
    return ((num16 & 0xF) == 10 ? 'A' : (num16 & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
void check(int x, int y, int n, int mat[8][8], int sumx, int sumy, int sumsc[29][29]) { // x и y - координаты, n - номер вхождения, mat - матрица; sumx, sumy, sumsc[][] - суммы индексов, по которым мы будем заполнять ячейки таблицы sumsc
    switch (n) {
        case 1: // Проверяем соседние ячейки рядом с первым вхождением буквы A
            if ((x-1 >= 0) && (mat[y][x-1] == 'B')) check(x-1, y, 2, mat, x, y, sumsc); // Также не забываем проверять выход за границы массива
            if ((x+1 <= 7) && (mat[y][x+1] == 'B')) check(x+1, y, 2, mat, x, y, sumsc);
            if ((y-1 >= 0) && (mat[y-1][x] == 'B')) check(x, y-1, 2, mat, x, y, sumsc);
            if ((y+1 <= 7) && (mat[y+1][x] == 'B')) check(x, y+1, 2, mat, x, y, sumsc);
            break;
        case 2: // Проверяем соседние ячейки рядом с первым вхождением буквы B
            if ((x-1 >= 0) && (mat[y][x-1] == 'B')) check(x-1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if ((x+1 <= 7) && (mat[y][x+1] == 'B')) check(x+1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if ((y-1 >= 0) && (mat[y-1][x] == 'B')) check(x, y-1, 3, mat, sumx + x, sumy + y, sumsc);
            if ((y+1 <= 7) && (mat[y+1][x] == 'B')) check(x, y+1, 3, mat, sumx + x, sumy + y, sumsc);
            break;
        default: // Проверяем соседние ячейки рядом со вторым вхождением буквы B (написано default, т.к. у нас всего 3 возможных случая, и поэтому можно написать default вместо case 3)
            if ((x-1 >= 0) && (mat[y][x-1] == 'A')) sumsc[sumy + y*2][sumx + x*2 - 1]++; // Значение ячейки таблицы sumsc с координатами sumy и sumx увеличивается при каждом вхождении ABBA
            if ((x+1 <= 7) && (mat[y][x+1] == 'A')) sumsc[sumy + y*2][sumx + x*2 + 1]++;
            if ((y-1 >= 0) && (mat[y-1][x] == 'A')) sumsc[sumy + y*2 - 1][sumx + x*2]++;
            if ((y+1 <= 7) && (mat[y+1][x] == 'A')) sumsc[sumy + y*2 + 1][sumx + x*2]++;
    }
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsc[29][29] = {0}; // Создание: матрицы для букв A и B; счётчика, который будет выводить кол-во ABBA; матрицы уникальных вхождений ABBA, по которой находим ответ
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Заполнение матрицы mat буквами A или B (остальные не нужны, поэтому они 0)
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    if (mat[y][x] == 'A') check(x, y, 1, mat, x, y, sumsc); // Заполнение матрицы sumsc вхождениями ABBA (y в ней - сумма всех координат y букв в ABBA, а x - аналогично сумма координат x)
    for (int y = 0; y < 29; y++)   for (int x = 0; x < 29; x++)   count += sumsc[y][x]; // Пробегаемся по матрице sumsc и увеличиваем счётчик, когда по данным координатам есть ABBA
    return count >> 1; // Т.к. у нас во всех случаях программа считает слово по 2 раза, мы можем просто разделить счётчик на 2 и получить ответ
}
int main() {
    int sample1[8] = {-1413863685, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\nABBA for sample2: %d", abba(sample1), abba(sample2));
    return 0;
}

/* Предыдущая версия, не идеальная
#include <stdio.h>             Контрольная работа №3. 
int hex(int n, int i) { // Перевод в 16-чную систему, n - число, i - четвёрка цифр числа (у каждого числа будет ровно 8 таких четвёрок, т.к. int занимает 32 байта 32/4=8)
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
void check(int x, int y, int n, int mat[8][8], int sumx, int sumy, int sumsc[29][29]) { // x и y - координаты, n - номер вхождения, mat - матрица; sumx, sumy, sumsc[][] - суммы индексов для проверки повторов
    switch (n) {
        case 1: // Проверяем соседние ячейки рядом с первым вхождением буквы A
            if (mat[y][x-1] == 'B') check(x-1, y, 2, mat, x, y, sumsc);
            if (mat[y][x+1] == 'B') check(x+1, y, 2, mat, x, y, sumsc);
            if (mat[y-1][x] == 'B') check(x, y-1, 2, mat, x, y, sumsc);
            if (mat[y+1][x] == 'B') check(x, y+1, 2, mat, x, y, sumsc);
            break;
        case 2: // Проверяем соседние ячейки рядом с первым вхождением буквы B
            if (mat[y][x-1] == 'B') check(x-1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y][x+1] == 'B') check(x+1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y-1][x] == 'B') check(x, y-1, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y+1][x] == 'B') check(x, y+1, 3, mat, sumx + x, sumy + y, sumsc);
            break;
        default: // Проверяем соседние ячейки рядом со вторым вхождением буквы B (написано default, т.к. у нас всего 3 возможных случая, и поэтому можно написать default вместо case 3)
            if (mat[y][x-1] == 'A') sumsc[sumy + y*2][sumx + x*2 - 1] = 1; // Единичка значит, что данная сумма координат sumy (координата y в sumsc) и сумма координат sumx (координата x в sumsc) встретились, при повторном вхождении ABBA значение ячейки не измениться, следовательно, ответ будет верным
            if (mat[y][x+1] == 'A') sumsc[sumy + y*2][sumx + x*2 + 1] = 1;
            if (mat[y-1][x] == 'A') sumsc[sumy + y*2 - 1][sumx + x*2] = 1;
            if (mat[y+1][x] == 'A') sumsc[sumy + y*2 + 1][sumx + x*2] = 1;
    }
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsc[29][29] = {0};// Создание: матрицы для букв A и B; счётчика, который будет выводить кол-во ABBA; матрицы уникальных вхождений ABBA, по которой находим ответ
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Заполнение матрицы mat буквами A или B (остальные не нужны, поэтому они 0)
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    if (mat[y][x] == 'A') check(x, y, 1, mat, x, y, sumsc); // Заполнение матрицы sumsc уникальными вхождениями ABBA (y в ней - сумма всех координат y букв в ABBA, а x - аналогично сумма координат x)
    for (int y = 0; y < 29; y++)   for (int x = 0; x < 29; x++)   if (sumsc[y][x]) count += 1; // Пробегаемся по матрице sumsc и увеличиваем счётчик, когда по данным координатам есть ABBA
    return count;
}
int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\nABBA for sample2: %d", abba(sample1), abba(sample2));
    return 0;
}
*/

/* Финальная версия (с отладкой)
#include <stdio.h>              Контрольная работа №3. 
int hex(int n, int i) { // Перевод в 16-чную систему
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
int check(int x, int y, int n, int mat[8][8], int sumx, int sumy, int sumsc[29][29]) { // x и y - координаты, n - номер вхождения, mat - матрица; sumx, sumy, sumsc[][] - суммы индексов для проверки повторов
    int a = 0, b = 0, x1 = 0, y1 = 0, x2 = 0, x3 = 0, x4 = 0, y2 = 0, y3 = 0, y4 = 0;
    switch (n) {
        case 1:
            if (mat[y][x-1] == 'B') a += check(x-1, y, 2, mat, x, y, sumsc);
            if (mat[y][x+1] == 'B') a += check(x+1, y, 2, mat, x, y, sumsc);
            if (mat[y-1][x] == 'B') a += check(x, y-1, 2, mat, x, y, sumsc);
            if (mat[y+1][x] == 'B') a += check(x, y+1, 2, mat, x, y, sumsc);
            return a;
        case 2:
            if (mat[y][x-1] == 'B') b += check(x-1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y][x+1] == 'B') b += check(x+1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y-1][x] == 'B') b += check(x, y-1, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y+1][x] == 'B') b += check(x, y+1, 3, mat, sumx + x, sumy + y, sumsc);
            return b;
        case 3:
            if (mat[y][x-1] == 'A') {
                x1 += sumx + x*2 - 1;
                y1 += sumy + y*2;
                if (sumsc[y1][x1]) return 0;
                sumsc[y1][x1] = 1;
            }
            if (mat[y][x+1] == 'A') {
                x2 += sumx + x*2 + 1;
                y2 += sumy + y*2;
                if (sumsc[y2][x2])  return 0;
                sumsc[y2][x2] = 1;
            }
            if (mat[y-1][x] == 'A') {
                x3 += sumx + x*2;
                y3 += sumy + y*2 - 1;
                if (sumsc[y3][x3])  return 0;
                sumsc[y3][x3] = 1;
            }
            if (mat[y+1][x] == 'A') {
                x4 += sumx + x*2;
                y4 += sumy + y*2 + 1;
                if (sumsc[y4][x4]) return 0;
                sumsc[y4][x4] = 1;
            }
            return (mat[y][x-1] == 'A') + (mat[y][x+1] == 'A') + (mat[y-1][x] == 'A') + (mat[y+1][x] == 'A');
    }
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsc[29][29] = {0};// Создание матрицы, где x - это столбцы, а y - строки, а также счётчика, который будет выводить кол-во ABBA
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Заполнение матрицы

    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            if (mat[y][x] == 'A') check(x, y, 1, mat, x, y, sumsc);

    for (int y = 0; y < 29; y++)
        for (int x = 0; x < 29; x++)
            if (sumsc[y][x]) count += 1;

    /* for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%s ", (mat[y][x] == 65 ? "A" : (mat[y][x] == 66 ? "B" : "-")));
        printf("\n");
    }
    for (int y = 0; y < 29; y++) {
        for (int x = 0; x < 29; x++) {
            if (sumsc[y][x])
            printf("%d(%d,%d) ", 1, y, x);
            printf("%d ", 0);
        }
        printf("\n");
    }

    return count;
}
int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\n", abba(sample1));
    printf("ABBA for sample2: %d\n", abba(sample2));
    return 0;
}
*/

/* 2 ревизия
#include <stdio.h>
int hex(int n, int i) {
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
int check(int s, int x, int y, int n, int mat[8][8], int sumx, int sumy, int *sumsx, int *sumsy) { // s - символ, x и y - координаты, n - номер вхождения
    if (s == 'A' && n == 1) {
        if (mat[y][x-1] == 'B') {
            sumx += (x-1);
            sumy += y;
            return check('B', x-1, y, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y][x+1] == 'B') {
            sumx += (x+1);
            sumy += y;
            return check('B', x+1, y, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y-1][x] == 'B') {
            sumx += x;
            sumy += (y-1);
            return check('B', x, y-1, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y+1][x] == 'B') {
            sumx += x;
            sumy += (y+1);
            return check('B', x, y+1, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        return 0;
    }
    if (s == 'B' && n == 2) {
        if (mat[y][x-1] == 'B') {
            sumx += (x-1);
            sumy += y;
            return check('B', x-1, y, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y][x+1] == 'B') {
            sumx += (x+1);
            sumy += y;
            return check('B', x+1, y, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y-1][x] == 'B') {
            sumx += x;
            sumy += (y-1);
            return check('B', x, y-1, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y+1][x] == 'B') {
            sumx += x;
            sumy += (y+1);
            return check('B', x, y+1, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        return 0;
    }
    if (s == 'B' && n == 3) {
        if (mat[y][x-1] == 'A') {
            sumx += (x-1);
            sumy += y;
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        if (mat[y][x+1]== 'A') {
            sumx += (x+1);
            sumy += y;
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        if (mat[y-1][x] == 'A') {
            sumx += x;
            sumy += (y-1);
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        if (mat[y+1][x] == 'A') {
            sumx += x;
            sumy += (y + 1);
            for (int i = 0; i < 64; i++)
                if ((sumsx[i] == sumx) || (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsx[64] = {0}, sumsy[64] = {0};// Создание матрицы, где x - это столбцы, а y - строки, а также счётчика, который будет выводить кол-во ABBA
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Присвоение значений матрице

    // Сама таблица:
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%s ", (mat[y][x] == 65 ? "A" : (mat[y][x] == 66 ? "B" : "-")));
        printf("\n");
    }

    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            if (mat[y][x] == 'A') {
                count += check(mat[y][x], x, y, 1, mat, 0, 0, sumsx, sumsy);
            }
        }
    return count;
}

int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\n\n", abba(sample1));
    printf("ABBA for sample2: %d\n", abba(sample2));
    return 0;
}
*/

/* 1 ревизия
#include <stdio.h>
int hex(int n, int i) {
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
int check(int s, int x, int y, int n, int c, int mat[8][8], int sumx, int sumy, int *sumsx, int *sumsy) { // s - символ, x и y - координаты, n - номер вхождения, c - кол-во подходящих соседних символов,
    if (s == 'A' && n == 1) {
        c += (mat[y][x-1] == 'B' ? 1 : 0) + (mat[y][x+1] == 'B' ? 1 : 0) + (mat[y-1][x] == 'B' ? 1 : 0) + (mat[y+1][x] == 'B' ? 1 : 0);
        if (mat[y][x-1] == 'B') {
            sumx += (x-1);
            sumy += y;
            return check('B', x-1, y, 2, c, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y][x+1] == 'B') {
            sumx += (x+1);
            sumy += y;
            return check('B', x+1, y, 2, c, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y-1][x] == 'B') {
            sumx += x;
            sumy += (y-1);
            return check('B', x, y-1, 2, c, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y+1][x] == 'B') {
            sumx += x;
            sumy += (y+1);
            return check('B', x, y+1, 2, c, mat, sumx, sumy, sumsx, sumsy);
        }
        return 0;
    }
    if (s == 'B' && n == 2) {
        c += (mat[y][x-1] == 'B' ? 1 : 0) + (mat[y][x+1] == 'B' ? 1 : 0) + (mat[y-1][x] == 'B' ? 1 : 0) + (mat[y+1][x] == 'B' ? 1 : 0);
        if (mat[y][x-1] == 'B') {
            sumx += (x-1);
            sumy += y;
            return check('B', x-1, y, 3, c, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y][x+1] == 'B') {
            sumx += (x+1);
            sumy += y;
            return check('B', x+1, y, 3, c, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y-1][x] == 'B') {
            sumx += x;
            sumy += (y-1);
            return check('B', x, y-1, 3, c, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y+1][x] == 'B') {
            sumx += x;
            sumy += (y+1);
            return check('B', x, y+1, 3, c, mat, sumx, sumy, sumsx, sumsy);
        }
        return 0;
    }
    if (s == 'B' && n == 3) {
        c += (mat[y][x-1] == 'A' ? 1 : 0) + (mat[y][x+1] == 'A' ? 1 : 0) + (mat[y-1][x] == 'A' ? 1 : 0) + (mat[y+1][x] == 'A' ? 1 : 0);
        if (mat[y][x-1] == 'A') {
            sumx += (x-1);
            sumy += y;
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return c;
        }
        if (mat[y][x+1]== 'A') {
            sumx += (x+1);
            sumy += y;
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return c;
        }
        if (mat[y-1][x] == 'A') {
            sumx += x;
            sumy += (y-1);
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return c;
        }
        if (mat[y+1][x] == 'A') {
            sumx += x;
            sumy += (y + 1);
            for (int i = 0; i < 64; i++)
                if ((sumsx[i] == sumx) || (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return c;
        }
        return 0;
    }
    return 0;
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsx[64] = {0}, sumsy[64] = {0};// Создание матрицы, где x - это столбцы, а y - строки, а также счётчика, который будет выводить кол-во ABBA
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Присвоение значений матрице

    // Сама таблица:
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%s ", (mat[y][x] == 65 ? "A" : (mat[y][x] == 66 ? "B" : "-")));
        printf("\n");
    }

    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            if (mat[y][x] == 'A') {
                count += check(mat[y][x], x, y, 1, 0, mat, 0, 0, sumsx, sumsy);
            }
        }
    return count;
}

int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\n\n", abba(sample1));
    printf("ABBA for sample2: %d\n", abba(sample2));
    return 0;
}
 */

/*#include <stdio.h>             Контрольная работа №3.
int hex(int n, int i) { // Перевод в 16-чную систему
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
int freecoord() {

}
int check(int s, int x, int y, int n, int mat[8][8], int sumx, int sumy, int *sumsx, int *sumsy) { // s - символ, x и y - координаты, n - номер вхождения, mat - матрица; sumx, sumy, sumsx[], sumsy[] - суммы индексов для проверки повторов
    switch (n) {
        case 1:
            if (mat[y][x-1] == 'B') {
                sumx += x + x - 1;
                sumy += y + y;
            }
            if  (mat[y][x+1] == 'B') {
                sumx += x + x + 1;
                sumy += y + y;
            }
            if (mat[y-1][x] == 'B') {
                sumx += x + x;
                sumy += y + y - 1;
            }
            if(mat[y+1][x] == 'B') {
                sumx += x + x;
                sumy += y + y + 1;
            }
            return check('B', x-1, y, 2, mat, sumx, sumy, sumsx, sumsy) + check('B', x+1, y, 2, mat, sumx, sumy, sumsx, sumsy) + check('B', x, y-1, 2, mat, sumx, sumy, sumsx, sumsy) + check('B', x, y+1, 2, mat, sumx, sumy, sumsx, sumsy);
        case 2:
            if (mat[y][x-1] == 'B') {
                sumx += (x-1);
                sumy += y;
            }
            if (mat[y][x+1] == 'B') {
                sumx += (x+1);
                sumy += y;
            }
            if (mat[y-1][x] == 'B') {
                sumx += x;
                sumy += (y-1);
            }
            if (mat[y+1][x] == 'B') {
                sumx += x;
                sumy += (y + 1);
            }
            return check('B', x-1, y, 3, mat, sumx, sumy, sumsx, sumsy) + check('B', x, y+1, 3, mat, sumx, sumy, sumsx, sumsy) + check('B', x, y-1, 3, mat, sumx, sumy, sumsx, sumsy) + check('B', x+1, y, 3, mat, sumx, sumy, sumsx, sumsy);
        case 3:
            if (mat[y][x-1] == 'A') {
                sumx += (x-1);
                sumy += y;
                int i = 0, j = 0;
                while (sumsx[i]) {
                    if (sumsx[i] == sumx)
                        return 0;
                    i++;
                }
                while (sumsy[j]) {
                    if (sumsy[j] == sumy)
                        return 0;
                    j++;
                }
                sumsx[i] = sumx;
                sumsy[j] = sumy;
            }
            if (mat[y][x+1]== 'A') {
                sumx += (x+1);
                sumy += y;
                int i = 0, j = 0;
                while (sumsx[i]) {
                    if (sumsx[i] == sumx)
                        return 0;
                    i++;
                }
                while (sumsy[j]) {
                    if (sumsy[j] == sumy)
                        return 0;
                    j++;
                }
                sumsx[i] = sumx;
                sumsy[j] = sumy;
            }
            if (mat[y-1][x] == 'A') {
                sumx += x;
                sumy += (y-1);
                int i = 0, j = 0;
                while (sumsx[i]) {
                    if (sumsx[i] == sumx)
                        return 0;
                    i++;
                }
                while (sumsy[j]) {
                    if (sumsy[j] == sumy)
                        return 0;
                    j++;
                }
                sumsx[i] = sumx;
                sumsy[j] = sumy;
            }
            if (mat[y+1][x] == 'A') {
                sumx += x;
                sumy += (y + 1);
                int i = 0, j = 0;
                while (sumsx[i]) {
                    if (sumsx[i] == sumx)
                        return 0;
                    i++;
                }
                while (sumsy[j]) {
                    if (sumsy[j] == sumy)
                        return 0;
                    j++;
                }
                sumsx[i] = sumx;
                sumsy[j] = sumy;
            }
            return (mat[y][x-1] == 'A') + (mat[y][x+1]== 'A') + (mat[y-1][x] == 'A') + (mat[y+1][x] == 'A');
        default: return 0;
    }
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, coord[128][128] = {0};// Создание матрицы, где x - это столбцы, а y - строки, а также счётчика, который будет выводить кол-во ABBA
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Заполнение матрицы

    // Сама таблица:
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%s ", (mat[y][x] == 65 ? "A" : (mat[y][x] == 66 ? "B" : "-")));
        printf("\n");
    }

//    for (int y = 0; y < 8; y++)
//        for (int x = 0; x < 8; x++) {
//            if (mat[y][x] == 'A') count += check('A', x, y, 1, mat, 0, 0, sumsx, sumsy);
//        }
    count += check('A', 0, 0, 1, mat, 0, 0, sumsx, sumsy);
    return count;
}
int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\n\n", abba(sample1));
    printf("ABBA for sample2: %d\n", abba(sample2));
    return 0;
}

*/

/*
#include <stdio.h>             Контрольная работа №3.
int hex(int n, int i) { // Перевод в 16-чную систему
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
int check(int x, int y, int n, int mat[8][8], int sumx, int sumy, int sumsc[29][29]) { // x и y - координаты, n - номер вхождения, mat - матрица; sumx, sumy, sumsc[][] - суммы индексов для проверки повторов
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0, x1 = 0, y1 = 0, x2 = 0, x3 = 0, x4 = 0, y2 = 0, y3 = 0, y4 = 0;
    switch (n) {
        case 1:
            if (mat[y][x-1] == 'B') a1 = check(x-1, y, 2, mat, x, y, sumsc);
            if (mat[y][x+1] == 'B') a2 = check(x+1, y, 2, mat, x, y, sumsc);
            if (mat[y-1][x] == 'B') a3 = check(x, y-1, 2, mat, x, y, sumsc);
            if (mat[y+1][x] == 'B') a4 = check(x, y+1, 2, mat, x, y, sumsc);
            return a1 + a2 + a3 + a4;
        case 2:
            if (mat[y][x-1] == 'B') b1 = check(x-1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y][x+1] == 'B') b2 = check(x+1, y, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y-1][x] == 'B') b3 = check(x, y-1, 3, mat, sumx + x, sumy + y, sumsc);
            if (mat[y+1][x] == 'B') b4 = check(x, y+1, 3, mat, sumx + x, sumy + y, sumsc);
            return b1 + b2 + b3 + b4;
        case 3:
            if (mat[y][x-1] == 'A') {
                x1 += sumx + x*2 - 1;
                y1 += sumy + y*2;
                if (sumsc[y1][x1]) return 0;
                sumsc[y1][x1] = 1;
            }
            if (mat[y][x+1] == 'A') {
                x2 += sumx + x*2 + 1;
                y2 += sumy + y*2;
                if (sumsc[y2][x2])  return 0;
                sumsc[y2][x2] = 1;
            }
            if (mat[y-1][x] == 'A') {
                x3 += sumx + x*2;
                y3 += sumy + y*2 - 1;
                if (sumsc[y3][x3])  return 0;
                sumsc[y3][x3] = 1;
            }
            if (mat[y+1][x] == 'A') {
                x4 += sumx + x*2;
                y4 += sumy + y*2 + 1;
                if (sumsc[y4][x4]) return 0;
                sumsc[y4][x4] = 1;
            }
            return (mat[y][x-1] == 'A') + (mat[y][x+1] == 'A') + (mat[y-1][x] == 'A') + (mat[y+1][x] == 'A');
    }
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsc[29][29] = {0};// Создание матрицы, где x - это столбцы, а y - строки, а также счётчика, который будет выводить кол-во ABBA
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Заполнение матрицы
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            if (mat[y][x] == 'A') count += check(x, y, 1, mat, x, y, sumsc);

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%s ", (mat[y][x] == 65 ? "A" : (mat[y][x] == 66 ? "B" : "-")));
        printf("\n");
    }
    for (int y = 0; y < 29; y++) {
        for (int x = 0; x < 29; x++) {
            if (sumsc[y][x])
                printf("%d(%d,%d) ", 1, y, x);
            printf("%d ", 0);
        }
        printf("\n");
    }
    return count;
}
int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\n\n", abba(sample1));
    printf("ABBA for sample2: %d\n", abba(sample2));
    return 0;
}

/* 2 ревизия
#include <stdio.h>
int hex(int n, int i) {
    int b = (n >> (32 - ((i+1) * 4))); // Таким образом мы разбиваем число в 2-чной системе на 4 бита, но отнимаем от 32, дабы начинать с самой левой четвёрки
    return ((b & 0xF) == 10 ? 'A' : (b & 0xF) == 11 ? 'B' : 0); // Для задания нам нужны только A и B, остальные значения будут 0
}
int check(int s, int x, int y, int n, int mat[8][8], int sumx, int sumy, int *sumsx, int *sumsy) { // s - символ, x и y - координаты, n - номер вхождения
    if (s == 'A' && n == 1) {
        if (mat[y][x-1] == 'B') {
            sumx += (x-1);
            sumy += y;
            return check('B', x-1, y, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y][x+1] == 'B') {
            sumx += (x+1);
            sumy += y;
            return check('B', x+1, y, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y-1][x] == 'B') {
            sumx += x;
            sumy += (y-1);
            return check('B', x, y-1, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y+1][x] == 'B') {
            sumx += x;
            sumy += (y+1);
            return check('B', x, y+1, 2, mat, sumx, sumy, sumsx, sumsy);
        }
        return 0;
    }
    if (s == 'B' && n == 2) {
        if (mat[y][x-1] == 'B') {
            sumx += (x-1);
            sumy += y;
            return check('B', x-1, y, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y][x+1] == 'B') {
            sumx += (x+1);
            sumy += y;
            return check('B', x+1, y, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y-1][x] == 'B') {
            sumx += x;
            sumy += (y-1);
            return check('B', x, y-1, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        if (mat[y+1][x] == 'B') {
            sumx += x;
            sumy += (y+1);
            return check('B', x, y+1, 3, mat, sumx, sumy, sumsx, sumsy);
        }
        return 0;
    }
    if (s == 'B' && n == 3) {
        if (mat[y][x-1] == 'A') {
            sumx += (x-1);
            sumy += y;
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        if (mat[y][x+1]== 'A') {
            sumx += (x+1);
            sumy += y;
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        if (mat[y-1][x] == 'A') {
            sumx += x;
            sumy += (y-1);
            for (int i = 0; i < 64; i++)
                if ( (sumsx[i] == sumx)|| (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        if (mat[y+1][x] == 'A') {
            sumx += x;
            sumy += (y + 1);
            for (int i = 0; i < 64; i++)
                if ((sumsx[i] == sumx) || (sumsy[i] == sumy))
                    return 0;
            for (int i = 0; i < 64; i++) {
                if (sumsx[i] == 0)
                    sumsx[i] == sumx;
                if (sumsy[i] == 0)
                    sumsy[i] == sumy;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}
int abba(int mas[8]) {
    int mat[8][8], count = 0, sumsx[64] = {0}, sumsy[64] = {0};// Создание матрицы, где x - это столбцы, а y - строки, а также счётчика, который будет выводить кол-во ABBA
    for (int y = 0; y < 8; y++)    for (int x = 0; x < 8; x++)    mat[y][x] = hex(mas[y], x); // Присвоение значений матрице

    // Сама таблица:
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            printf("%s ", (mat[y][x] == 65 ? "A" : (mat[y][x] == 66 ? "B" : "-")));
        printf("\n");
    }

    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            if (mat[y][x] == 'A') {
                count += check(mat[y][x], x, y, 1, mat, 0, 0, sumsx, sumsy);
            }
        }
    return count;
}

int main() {
    int sample1[8] = {-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] = {-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("ABBA for sample1: %d\n\n", abba(sample1));
    printf("ABBA for sample2: %d\n", abba(sample2));
    return 0;
}
*/
